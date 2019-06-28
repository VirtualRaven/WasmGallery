#include "layout.hpp"
#define INCLUDE_DATA
#include "data.hpp"
#include "allData.hpp"
using namespace Layout;


static_assert(sizeof(Data::picSize)/sizeof(PictureSize)==Data::NumPictures, "NumPictures not set correctly" );

#ifdef TARGET_WASM
    constexpr int  PAGE_SIZE=65536; 
    extern unsigned char __heap_base;
    const int __heap_addr =   reinterpret_cast<int>(&__heap_base);   
    typedef Layout::PictureSizeDouble PSB;
    extern "C"{
        PSB  *calcSize= reinterpret_cast<PSB*>(__heap_addr);

        void init(){
            const int sizeLeft=__builtin_wasm_memory_size(0)*PAGE_SIZE-__heap_addr;
            const int sizeRequired = Data::NumPictures* sizeof(Layout::PictureSizeDouble);
            if(sizeLeft < sizeRequired){
                const int extraPages =  1+(sizeRequired - sizeLeft)/PAGE_SIZE ;
                __builtin_wasm_memory_grow(0,extraPages);
            }
        }
    }
#endif
namespace Calculated
{
    double ScaleFactor[Data::NumPictures];
    int Row[Data::NumPictures];
} 

    __attribute__((__used__))
    const int PicLen = Data::NumPictures; 

template<typename T,typename F>
inline auto min(const T* a, int start, int end, F f){
    if(start>=end){
        return f(a[end]);
    }
    else{
        auto minRest{min(a,start+1,end,f)};
        return f(a[start]) < minRest  ? f(a[start]) : minRest; 
    }
} 

template<typename T,typename F> 
inline auto sum(const T* a, int start, int end, F f)-> decltype(f(a[start]))
{
    auto c = f(a[start]);
    return  start == end ? c : c + sum(a,start+1,end,f);
}

template<typename T1,typename T2,typename F>
inline void modify(T1* dst,T2* src ,int start , int end, F f){
    for(auto i = start; i <= end; i++){
        dst[i]=f(src[i]);
    }
} 

Window Layout::wnd={0,0,0,0};
const  void * metaPtr=reinterpret_cast<const void* >(&Data::picMeta);
 __attribute__((__used__))
void Layout::calcScaleFactors(Window w,int offset,bool scrollSubtracted){
    auto row= [&w](int start,int end, double& scale, bool LastRow )-> bool{
        if(LastRow){
            scale=1.0;
            return true;
        }
        else{
            auto minH = min(Data::picSize,start,end,[](PictureSize x){return x.height;});
            modify(Calculated::ScaleFactor,Data::picSize,start,end,[minH](PictureSize x){ return minH / static_cast<double>(x.height); } );
            auto sumW = sum(Data::picSize,start,end,[minH](PictureSize x){
                return static_cast<double>(x.width) * minH / static_cast<double>(x.height); 
            });
            auto nElems = end-start+1;
            scale = 1.002*sumW/( w.width-nElems*w.excess);
            return scale > 1.0;
        }
    };

    int start =offset,end=offset,rowI=0;
    double totalHeight=0;
    while(end < Data::NumPictures ){
        double scale;
        while( end < Data::NumPictures && !row(start,end,scale,false)){
            end++;
        }

        if( end >= Data::NumPictures){
            row(start,end,scale,true);
        }
        
        Layout::PictureSizeDouble size;
        for(int i = start; i <= end; i++){
            const auto scaleFactor = Calculated::ScaleFactor[i]/scale;

            Calculated::ScaleFactor[i]=scaleFactor;
            Calculated::Row[i]=rowI;
            size = {
                    .width=Data::picSize[i].width*scaleFactor,
                    .height=Data::picSize[i].height*scaleFactor  
            };
            #ifdef TARGET_WASM
            calcSize[i]=size;
            #endif
        }
        //All pictures ahve the same height;
        totalHeight+=size.height+w.excess;

        //Scroll 
        if(!scrollSubtracted && 
            w.scrollBar > 0.0 && 
            totalHeight >  w.height 
         ){
            w.width-= w.scrollBar;
            return calcScaleFactors(w,offset,true);
        }
        start=++end;
        rowI++;
    }
}

