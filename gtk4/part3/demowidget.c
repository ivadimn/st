/*
Это чрезвычайно простой аннотированный файл .c, который реализует пользовательский
* виджет в gtk4 с gobject. Все, что он делает, это подклассифицирует GtkWidget и создает
* виджет, который является просто кнопкой.
*
* Требуется: glib >= 2.44, gtk4 >= 4.0.0
*
* Это шаблон для FINAL (в отличие от DERIVABLE типа gobject.
* Финальные типы проще. Вы делаете большую часть работы в файле C и просто
* раскрываете несколько открытых методов в файле .h.
*
* Другими словами, поскольку его нельзя подклассифицировать дальше, 
* вы вообще не раскрываете публично
* внутренности объекта, и все это просто определяется и обрабатывается
* с помощью стандартных функций GObject/GTK.
*/

#include "demowidget.h"

/* GLOBAL FOR PROPERTIES */

enum property_types
{
    PROP_LABEL = 1,
    N_PROPERTIES
};

static GParamSpec *properties[N_PROPERTIES];

/* GLOBAL FOR SIGNALS */
enum signal_types
{
    FOOBAR,
    LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];


/* INTERNAL DECLARATION */

/*
* Это не является строго необходимым, так как мы сохранили все в естественном рабочем
* порядке ниже. Но G_DEFINE_TYPE *не* предоставляет объявления для этих
* функций деструктора, поэтому, если вы измените порядок конструкторов и
* деструкторов, определенных ниже, вы получите ошибку.
*/

static void demo_widget_dispose(GObject *object);
static void demo_widget_finalize(GObject *object);

/* GOBJECT DEFINITION */

/*
* Сначала создайте основную структуру, содержащую внутренности объекта.
* Следуйте формату подчеркивания, за которым следует имя типа CamelCase,  
* которое вы создали в заголовочном файле. Typedef автоматически генерируется
* макросами и, как ожидается, будет определен здесь.
*/

struct _DemoWidget
{
    /*
    * тип подкласса — убедитесь, что вы *не* используете указатель. Сохраните это как
    * первый член.
    */
    GtkWidget parent_instance; 

    /*
    * Здесь размещаются пользовательские мясо и картофель. Сейчас мы просто создаем
    * кнопку. Здесь вы *используете* указатели, когда хотите включить другие
    * объекты в структуру.
    */
   GtkWidget *button;
   guint timeout;
};

/*
* как только основная структура определена, как указано выше, вот следующий макрос. Убедитесь, что
* это идет до того, как делать что-либо еще. Порядок имеет значение.
*
* Первые два аргумента макроса являются шаблонными. Последний — стандартный
* макрос TYPE с заглавной буквы *того, что вы подклассифицируете.* Самый нижний, 
* который вы можете использовать, — это
* G_TYPE_OBJECT для необработанного gobject. В этом случае мы подклассифицируем
* GtkWidget, поэтому этот макрос типа указан ниже.
*/
G_DEFINE_TYPE(DemoWidget, demo_widget, GTK_TYPE_WIDGET)

/* PRIVATE INTERNAL FUNCTIONS */

static gboolean foobar_signal_source_func(gpointer user_data)
{
    DemoWidget *self = DEMO_WIDGET(user_data);
    g_signal_emit(self, signals[FOOBAR], 0);

    return G_SOURCE_CONTINUE;
}

/* PROPERTIES - GETTERS AND SETTERS*/

static void demo_widget_set_property(GObject *object,
                guint property_id,
                const GValue *value,
                GParamSpec *pspec)
{
    DemoWidget *self = DEMO_WIDGET(object);

    switch(property_id)
    {
        case PROP_LABEL:
            demo_widget_set_label(self, g_value_get_string(value));
            break;
        default:
            /* у нас нет других свойств */
            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
            break;
        
    }

}

static void demo_widget_get_property(GObject *object,
                guint property_id,
                GValue *value,
                GParamSpec *pspec)
{
    DemoWidget *self = DEMO_WIDGET(object);

    switch (property_id)
    {
    case PROP_LABEL:
        g_value_set_string(value,
                    gtk_button_get_label(GTK_BUTTON(self->button)));
        break;
    
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
        break;
    }
}

/* METHOD DEFINITIONS */

/*
* эта функция используется для построения виджета. Обратите внимание, что хотя в документации упоминается
* что-то как функция 'instance_init', подпрограмма на самом деле
* называется *_init, а не *_instance_init. Это меня сначала смутило.
*/

static void demo_widget_init(DemoWidget *self)
{
    /* Не обязательно, но это полезное сокращение. */
    GtkWidget *widget = GTK_WIDGET(self);
    
    self->button = gtk_button_new_with_label("Hello world!");
    gtk_widget_set_hexpand(self->button, TRUE);
    gtk_widget_set_parent(self->button, widget);

    /* испустить наш сигнал */

    self->timeout = g_timeout_add(5000, foobar_signal_source_func, self);
}

/*
* Это один из этапов процесса деструктора вместе с _finalize.
* Здесь вы в основном уничтожаете элементы, которые подсчитываются ссылками (например, GObject-y
* stuff), а не нет (например, строка или указатель FILE *, которые должны
* быть освобождены / закрыты, а не быть отброшенными).
*
* Важно помнить, что этот метод может быть вызван несколько раз. 
* Не учитывать это является ошибкой программиста. Если вы отмените ссылку на GObject, который
* уже имеет счетчик ссылок 0, вы получите ошибку времени выполнения. См. ниже
* о том, как мы это учитываем.
*
* См. Часть 1B этой серии о проблемах, с которыми вы можете столкнуться, если вы не будете
* с этим работать правильно.
*
* См. также:
* https://developer.gnome.org/gobject/stable/howto-gobject-destruction.html   
*/

static void demo_widget_dispose(GObject *object)
{
    DemoWidget *self = DEMO_WIDGET(object);

    /*
    * g_clear_pointer — очень полезная функция. Она вызывает функцию по вашему выбору,
    * чтобы отменить ссылку или освободить указатель, а затем устанавливает этот указатель в NULL.
    * Если она вызывается для указателя NULL, она просто ничего не делает. Это позволяет
    * идеально решить проблему многократного вызова _dispose.
    *
    * Здесь gtk_widget_unparent — это стандартная функция GTK для отделения
    * дочернего виджета от его родительского, что отменяет ссылку на этот виджет за кулисами.
    *
    * Обратите внимание, что g_clear_pointer принимает указатель *на* gpointer, а не
    * простой gpointer. Это необходимо для того, чтобы функция обнулила
    * указатель.
    */
   g_clear_pointer(&self->button, gtk_widget_unparent);

   /*
    * Последний шаг: цепочка (шаблон)
    *
    * Это называется «цепочкой» в документации gobject. *_parent_class
    * автоматически генерируется макросами - согласно gtype.h, это статическая
    * переменная, указывающая на родительский класс.
   */

    G_OBJECT_CLASS(demo_widget_parent_class)->dispose(object);
}

/*
* Вторая и последняя стадия процесса уничтожения. См. _finalize выше для
* дополнительной информации. Пока нам нечего сюда вставить, но мы включаем это для
* потомков и для легкого добавления позже; поэтому мы просто вручную соединяем на данный момент.
*/

static void demo_widget_finalize(GObject *object)
{
    DemoWidget *self = DEMO_WIDGET(object);
    if (self->timeout)
    {
        g_source_remove(self->timeout);
    }
    
    
    /* --- */

    /*
    * Всегда связывайтесь с родительским классом; как и в случае с dispose(), finalize()
    * автоматически генерируется и, таким образом, всегда гарантированно существует в родительском классе
    * таблица виртуальных функций
    */

    G_OBJECT_CLASS(demo_widget_parent_class)->finalize(object);
}

/*
* этот метод запускается в первый раз, когда класс *когда-либо* используется, но не
* снова.

* См.:
* https://developer.gnome.org/gobject/stable/howto-gobject-destruction.html
* для получения дополнительной информации о том, что вам нужно поместить в эту подпрограмму 
* относительно деструкторов.
*
* Примечание: я все время путался в том, что означает 'klass' и почему он пишется
* именно так. Это просто для того, чтобы избежать использования токена 'class' сам по себе, который является
* зарезервированным словом c++. Вы можете назвать его как-то по-другому, например 'gclass', если хотите,
* но он идиоматически называется 'klass' уже более 20 лет, так что,
* вероятно, лучше просто придерживаться этого.
*/

static void demo_widget_class_init(DemoWidgetClass *klass)
{
    /* Создайте стенографию, чтобы избежать некоторых приведений. */
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    GParamFlags default_flags = 
        G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS | G_PARAM_EXPLICIT_NOTIFY;

    /*
    * Сопоставьте «виртуальные функции» dispose и finalize с функциями
    *, которые мы определили выше.
    */

    object_class->dispose = demo_widget_dispose;
    object_class->finalize = demo_widget_finalize;

    object_class->set_property = demo_widget_set_property;
    object_class->get_property = demo_widget_get_property;

    /* свойства */

    properties[PROP_LABEL] = g_param_spec_string("label",
            "Button lable",
            "Textual label for our lovely button",
            /* по умолчанию */ "Hello, world!",
            default_flags);

    g_object_class_install_properties(object_class, N_PROPERTIES, properties);

    /* сигналы */

    signals[FOOBAR] = g_signal_new_class_handler("foobar",
                        G_OBJECT_CLASS_TYPE(object_class), 
                        G_SIGNAL_RUN_LAST,
                        /* нет функции обработки по умолчанию */
                        NULL,
                        /* накопитель, пользовательские данные для накопителя, маршаллер*/
                        NULL, NULL, NULL,
                        /* значение не возвращает и парамеироы нет */
                        G_TYPE_NONE, 0
                        );

    /*
    * Сообщите нашему виджету, какой тип «менеджера компоновки» использовать, чтобы он знал,
    * как расположить виджеты. Тип Box — хороший вариант по умолчанию.
    */
    gtk_widget_class_set_layout_manager_type(GTK_WIDGET_CLASS(klass),
                    GTK_TYPE_BOX_LAYOUT);
}

void demo_widget_set_label(DemoWidget *self, const char *label)
{
    gtk_button_set_label(GTK_BUTTON(self->button),label);
    g_object_notify_by_pspec(G_OBJECT(self), properties[PROP_LABEL]);
}

/*
* и наконец, вот фактическое определение нашей публичной функции для создания
* экземпляра нашего объекта.
*
* Он принимает GType типа GObject, за которым (необязательно) следуют пары имя/значение
* для установки «свойств» объекта, за которыми следует NULL, когда вы закончите. Поскольку
* у нас нет никаких свойств, которые мы собираемся инстанцировать, мы просто передаем NULL
* после GType. Мы обсудим свойства GObject позже.
*/

GtkWidget* demo_widget_new()
{
    return g_object_new(DEMO_TYPE_WIDGET, NULL);
}




