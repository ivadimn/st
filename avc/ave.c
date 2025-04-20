#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

int main()
{
    AVFormatContext *format_context = avformat_alloc_context();
    avformat_open_input(&format_context, "bbb.mp4", NULL, NULL);

    printf("Format %s, duration %ld us\n", format_context->iformat->long_name,
            format_context->duration);

    /* Чтобы получить доступ к потокам, 
    * нам нужно прочитать данные с носителя. 
    * Это делает функция avformat_find_stream_info. 
    * Теперь pFormatContext-> nb_streams будет содержать количество потоков, 
    * а pFormatContext-> streams[i] даст нам i-й по счёту поток (AVStream).
    */
    
    avformat_find_stream_info(format_context, NULL);

    for (size_t i = 0; i < format_context->nb_streams; i++)
    {
        /*
        * Для каждого потока мы собираемся сохранить AVCodecParameters, 
        * описывающий свойства кодека, используемого i-м потоком:
        */
        AVCodecParameters *codec_par = format_context->streams[i]->codecpar;
        /*
         * Используя свойства кодеков можем найти соответствующий, 
         * запрашивая функцию avcodec_find_decoder, 
         * также можем найти зарегистрированный декодер 
         * для идентификатора кодека и вернуть AVCodec — компонент, 
         * который знает, как кодировать и декодировать поток:
        */
        AVCodec *codec = avcodec_find_decoder(codec_par->codec_id);

        if (codec_par->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            printf("Video Codec: resolution %d x %d\n", codec_par->width, codec_par->height);
        }
        else if(codec_par->codec_type == AVMEDIA_TYPE_AUDIO) 
        {
            printf("Audio Codec: %d, channels, sample rate%d\n", codec_par->channels, codec_par->sample_rate);
        }
        printf("\tCodec %s ID %d bit_rate %ld\n", codec->long_name, codec->id, codec_par->bit_rate);

        /* С помощью кодека выделяем память для AVCodecContext, 
        * который будет содержать контекст для нашего процесса декодирования/кодирования. 
        * Но затем нужно заполнить этот контекст кодека параметрами CODEC — 
        * мы делаем это с помощью avcodec_parameters_to_context.

        * После того, как мы заполнили контекст кодека, необходимо открыть кодек. 
        * Вызываем функцию avcodec_open2 и затем можем ее использовать:
        */
        AVCodecContext *codec_context = avcodec_alloc_context(codec);
        avcodec_parameters_to_context(codec_context, codec_par);
        avcodec_open2(codec_context, codec, NULL);

        /*
        * Теперь мы собираемся прочитать пакеты из потока и декодировать их в кадры, 
        * но сначала нам нужно выделить память для обоих компонентов (AVPacket и AVFrame).
        */
       AVPacket *packet = av_packet_alloc();
       AVFrame *frame = av_frame_alloc();



        printf("------------------------------------------------------------------------\n");
    }
        
    avformat_close_input(&format_context);
    avformat_free_context(format_context);
    return 0;
}