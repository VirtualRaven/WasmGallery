#ifndef LAYOUT_H
#define LAYOUT_H
namespace Layout
{
    template<typename T>
    struct PictureSizeT
    {
        T width;
        T height;
    };

    struct PictureMeta {
        const char * Name;
        const char * Id;
        const char * Colour;
        char16_t thumbnailSizes[3];
        char NameLen;
    };



    typedef PictureSizeT<char16_t> PictureSize;
    typedef PictureSizeT<double> PictureSizeDouble;

    struct Window {
        double width;
        double height;
        double scrollBar;
        double excess;
    };
    extern "C"{
        extern void calcScaleFactors(Window w, int offset=0,bool scrollSubtracted=false );
        extern void genPicTbl();
        extern Window wnd;
    }
    
};

#endif