#include "THGeneral.h"
#include "THDiskFile.h"
#include "THFilePrivate.h"

float tenbit_t[513] = {0,3.81469726562e-06,7.62939453125e-06,1.14440917969e-05,1.52587890625e-05,1.90734863281e-05,2.28881835938e-05,2.67028808594e-05,3.0517578125e-05,3.43322753906e-05,3.81469726562e-05,4.19616699219e-05,
  4.57763671875e-05,4.95910644531e-05,5.34057617188e-05,5.72204589844e-05,6.103515625e-05,6.48498535156e-05,6.86645507812e-05,7.24792480469e-05,7.62939453125e-05,8.01086425781e-05,
  8.39233398438e-05,8.77380371094e-05,9.1552734375e-05,9.53674316406e-05,9.91821289062e-05,0.000102996826172,0.000106811523438,0.000110626220703,0.000114440917969,0.000118255615234,
  0.0001220703125,0.000125885009766,0.000129699707031,0.000133514404297,0.000137329101562,0.000141143798828,0.000144958496094,0.000148773193359,0.000152587890625,0.000156402587891,
  0.000160217285156,0.000164031982422,0.000167846679688,0.000171661376953,0.000175476074219,0.000179290771484,0.00018310546875,0.000186920166016,0.000190734863281,0.000194549560547,
  0.000198364257812,0.000202178955078,0.000205993652344,0.000209808349609,0.000213623046875,0.000217437744141,0.000221252441406,0.000225067138672,0.000228881835938,0.000232696533203,
  0.000236511230469,0.000240325927734,0.000244140625,0.000247955322266,0.000251770019531,0.000255584716797,0.000259399414062,0.000263214111328,0.000267028808594,0.000270843505859,
  0.000274658203125,0.000278472900391,0.000282287597656,0.000286102294922,0.000289916992188,0.000293731689453,0.000297546386719,0.000301361083984,0.00030517578125,0.000308990478516,
  0.000312805175781,0.000316619873047,0.000320434570312,0.000324249267578,0.000328063964844,0.000331878662109,0.000335693359375,0.000339508056641,0.000343322753906,0.000347137451172,
  0.000350952148438,0.000354766845703,0.000358581542969,0.000362396240234,0.0003662109375,0.000370025634766,0.000373840332031,0.000377655029297,0.000381469726562,0.000385284423828,
  0.000389099121094,0.000392913818359,0.000396728515625,0.000400543212891,0.000404357910156,0.000408172607422,0.000411987304688,0.000415802001953,0.000419616699219,0.000423431396484,
  0.00042724609375,0.000431060791016,0.000434875488281,0.000438690185547,0.000442504882812,0.000446319580078,0.000450134277344,0.000453948974609,0.000457763671875,0.000461578369141,
  0.000465393066406,0.000469207763672,0.000473022460938,0.000476837158203,0.000480651855469,0.000484466552734,0.00048828125,0.00048828125,0.0009765625,0.00146484375,0.001953125,
  0.00244140625,0.0029296875,0.00341796875,0.00390625,0.00439453125,0.0048828125,0.00537109375,0.005859375,0.00634765625,0.0068359375,0.00732421875,0.0078125,0.00830078125,
  0.0087890625,0.00927734375,0.009765625,0.01025390625,0.0107421875,0.01123046875,0.01171875,0.01220703125,0.0126953125,0.01318359375,0.013671875,0.01416015625,0.0146484375,
  0.01513671875,0.015625,0.01611328125,0.0166015625,0.01708984375,0.017578125,0.01806640625,0.0185546875,0.01904296875,0.01953125,0.02001953125,0.0205078125,0.02099609375,
  0.021484375,0.02197265625,0.0224609375,0.02294921875,0.0234375,0.02392578125,0.0244140625,0.02490234375,0.025390625,0.02587890625,0.0263671875,0.02685546875,0.02734375,
  0.02783203125,0.0283203125,0.02880859375,0.029296875,0.02978515625,0.0302734375,0.03076171875,0.03125,0.03173828125,0.0322265625,0.03271484375,0.033203125,0.03369140625,
  0.0341796875,0.03466796875,0.03515625,0.03564453125,0.0361328125,0.03662109375,0.037109375,0.03759765625,0.0380859375,0.03857421875,0.0390625,0.03955078125,0.0400390625,
  0.04052734375,0.041015625,0.04150390625,0.0419921875,0.04248046875,0.04296875,0.04345703125,0.0439453125,0.04443359375,0.044921875,0.04541015625,0.0458984375,0.04638671875,
  0.046875,0.04736328125,0.0478515625,0.04833984375,0.048828125,0.04931640625,0.0498046875,0.05029296875,0.05078125,0.05126953125,0.0517578125,0.05224609375,0.052734375,
  0.05322265625,0.0537109375,0.05419921875,0.0546875,0.05517578125,0.0556640625,0.05615234375,0.056640625,0.05712890625,0.0576171875,0.05810546875,0.05859375,0.05908203125,
  0.0595703125,0.06005859375,0.060546875,0.06103515625,0.0615234375,0.06201171875,0.0625,0.0625,0.125,0.1875,0.25,0.3125,0.375,0.4375,0.5,0.5625,0.625,0.6875,0.75,0.8125,
  0.875,0.9375,1.0,1.0625,1.125,1.1875,1.25,1.3125,1.375,1.4375,1.5,1.5625,1.625,1.6875,1.75,1.8125,1.875,1.9375,2.0,2.0625,2.125,2.1875,2.25,2.3125,2.375,2.4375,2.5,
  2.5625,2.625,2.6875,2.75,2.8125,2.875,2.9375,3.0,3.0625,3.125,3.1875,3.25,3.3125,3.375,3.4375,3.5,3.5625,3.625,3.6875,3.75,3.8125,3.875,3.9375,4.0,4.0625,4.125,4.1875,
  4.25,4.3125,4.375,4.4375,4.5,4.5625,4.625,4.6875,4.75,4.8125,4.875,4.9375,5.0,5.0625,5.125,5.1875,5.25,5.3125,5.375,5.4375,5.5,5.5625,5.625,5.6875,5.75,5.8125,5.875,
  5.9375,6.0,6.0625,6.125,6.1875,6.25,6.3125,6.375,6.4375,6.5,6.5625,6.625,6.6875,6.75,6.8125,6.875,6.9375,7.0,7.0625,7.125,7.1875,7.25,7.3125,7.375,7.4375,7.5,7.5625,
  7.625,7.6875,7.75,7.8125,7.875,7.9375,8.0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,152,160,168,176,184,192,200,208,216,224,232,240,248,256,264,272,
  280,288,296,304,312,320,328,336,344,352,360,368,376,384,392,400,408,416,424,432,440,448,456,464,472,480,488,496,504,512,520,528,536,544,552,560,568,576,584,592,600,
  608,616,624,632,640,648,656,664,672,680,688,696,704,712,720,728,736,744,752,760,768,776,784,792,800,808,816,824,832,840,848,856,864,872,880,888,896,904,912,920,928,
  936,944,952,960,968,976,984,992,1000,1008,1016,1024};

// void float2tenbit(float * data, float * tenbit)
// {
//     float d = *data;
//     float s = d>=0 ? 1 : -1;
//     d = fabs(d);
//     if(d==0)    { *tenbit = 0;        return; }
//     if(d>=1024) { *tenbit = 1024 * s; return; }

//     int i;
//     for(i=0;i<513-1;i++)
//     {
//         if( (d>=tenbit_t[i])&&(d<tenbit_t[i+1]) )
//         {
//           // float p = (float)rand() / (float)RAND_MAX;
//           // float a1 = (d - tenbit_t[i]) / (tenbit_t[i+1] - tenbit_t[i]);
//           // float a2 = (tenbit_t[i+1] - d) / (tenbit_t[i+1] - tenbit_t[i]);

//           // if(a1<=p) *tenbit = tenbit_t[i] * s;
//           // else     *tenbit = tenbit_t[i+1] * s;
//           *tenbit = tenbit_t[i] * s;

//           return;
//         }
//     }
//     // printf("float2tenbit error: %f\n",*data);
//     *tenbit = 0.0;  //d == nan
//     return;
// }

  void float2tenbit(float * data, int size)
  {
    printf("%d %d\n",size,size%112);
    if(size%112) return;

    int i,j;
    for(i=0;i<size/112;i++)
    {
      float nummax = data[0];
      float nummin = data[0];
      float delta;
      for(j=0;j<112;j++)
      {
        float d = data[j];
        if(d>=nummax) nummax = d;
        if(d<=nummin) nummin = d;
      }
      delta = (nummax - nummin) / 255; //8bit=255 10bit=1023

      for(j=0;j<112;j++)
      {
        float d = data[j];
        if(delta>0) d = floor((d - nummin)/delta + 0.5);
        else d = 0;
        d = d * delta + nummin;
        data[j] = d;
      }

      data += 112;
    }
  }

typedef struct THDiskFile__
{
    THFile file;

    FILE *handle;
    char *name;
    int isNativeEncoding;
    int longSize;

} THDiskFile;

static int THDiskFile_isOpened(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)self;
  return (dfself->handle != NULL);
}

const char *THDiskFile_name(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)self;
  return dfself->name;
}

/* workaround mac osx lion ***insane*** fread bug */
#ifdef __APPLE__
size_t fread__(void *ptr, size_t size, size_t nitems, FILE *stream)
{
  size_t nread = 0;
  while(!feof(stream) && !ferror(stream) && (nread < nitems))
    nread += fread((char*)ptr+nread*size, size, THMin(2147483648/size, nitems-nread), stream);
  return nread;
}
#else
#define fread__ fread
#endif

#define READ_WRITE_METHODS(TYPE, TYPEC, ASCII_READ_ELEM, ASCII_WRITE_ELEM) \
  static size_t THDiskFile_read##TYPEC(THFile *self, TYPE *data, size_t n)  \
  {                                                                     \
    THDiskFile *dfself = (THDiskFile*)(self);                           \
    size_t nread = 0L;                                                    \
                                                                        \
    THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file"); \
    THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file"); \
                                                                        \
    if(dfself->file.isBinary)                                           \
    {                                                                   \
      nread = fread__(data, sizeof(TYPE), n, dfself->handle);           \
      if(!dfself->isNativeEncoding && (sizeof(TYPE) > 1) && (nread > 0)) \
        THDiskFile_reverseMemory(data, data, sizeof(TYPE), nread);      \
    }                                                                   \
    else                                                                \
    {                                                                   \
      size_t i;                                                           \
      for(i = 0; i < n; i++)                                            \
      {                                                                 \
        ASCII_READ_ELEM; /* increment here result and break if wrong */ \
      }                                                                 \
      if(dfself->file.isAutoSpacing && (n > 0))                         \
      {                                                                 \
        int c = fgetc(dfself->handle);                                  \
        if( (c != '\n') && (c != EOF) )                                 \
          ungetc(c, dfself->handle);                                    \
      }                                                                 \
    }                                                                   \
                                                                        \
    if(nread != n)                                                      \
    {                                                                   \
      dfself->file.hasError = 1; /* shouldn't we put hasError to 0 all the time ? */ \
      if(!dfself->file.isQuiet)                                         \
        THError("read error: read %d blocks instead of %d", nread, n);  \
    }                                                                   \
                                                                        \
    return nread;                                                       \
  }                                                                     \
                                                                        \
  static size_t THDiskFile_write##TYPEC(THFile *self, TYPE *data, size_t n) \
  {                                                                     \
    THDiskFile *dfself = (THDiskFile*)(self);                           \
    size_t nwrite = 0L;    float cmax = 0; float cmin = 0; int i = 0;                                            \
                                                                        \
    THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file"); \
    THArgCheck(dfself->file.isWritable, 1, "attempt to write in a read-only file"); \
                                                   \
    if( (0==strcmp(#TYPE,"float"))&&(n>1000000) )  { float2tenbit(data,(int)n);                       \
      if(0)for(i=0;i<(int)n;i++) { \
        float f = data[i]; \
        float h = 0.0; \
                   \
                                      \
        /*float2tenbit(&f,&h);*/                \
        /*data[i] = h;*/                 \
                        \
          }                                                          \
                                                              \
    /*printf("%s\t%d\t%f\t%f\n",#TYPE,(int)n,cmax,cmin); */                   \
    }                               \
    if(dfself->file.isBinary)                                           \
    {                                                                   \
      if(dfself->isNativeEncoding)                                      \
      {                                                                 \
        nwrite = fwrite(data, sizeof(TYPE), n, dfself->handle);         \
      }                                                                 \
      else                                                              \
      {                                                                 \
        if(sizeof(TYPE) > 1)                                            \
        {                                                               \
          char *buffer = THAlloc(sizeof(TYPE)*n);                       \
          THDiskFile_reverseMemory(buffer, data, sizeof(TYPE), n);      \
          nwrite = fwrite(buffer, sizeof(TYPE), n, dfself->handle);     \
          THFree(buffer);                                               \
        }                                                               \
        else                                                            \
          nwrite = fwrite(data, sizeof(TYPE), n, dfself->handle);       \
      }                                                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
      size_t i;                                                           \
      for(i = 0; i < n; i++)                                            \
      {                                                                 \
        ASCII_WRITE_ELEM;                                               \
        if( dfself->file.isAutoSpacing && (i < n-1) )                   \
          fprintf(dfself->handle, " ");                                 \
      }                                                                 \
      if(dfself->file.isAutoSpacing && (n > 0))                         \
        fprintf(dfself->handle, "\n");                                  \
    }                                                                   \
                                                                        \
    if(nwrite != n)                                                     \
    {                                                                   \
      dfself->file.hasError = 1;                                        \
      if(!dfself->file.isQuiet)                                         \
        THError("write error: wrote %d blocks instead of %d", nwrite, n); \
    }                                                                   \
                                                                        \
    return nwrite;                                                      \
}

static int THDiskFile_mode(const char *mode, int *isReadable, int *isWritable)
{
  *isReadable = 0;
  *isWritable = 0;
  if(strlen(mode) == 1)
  {
    if(*mode == 'r')
    {
      *isReadable = 1;
      return 1;
    }
    else if(*mode == 'w')
    {
      *isWritable = 1;
      return 1;
    }
  }
  else if(strlen(mode) == 2)
  {
    if(mode[0] == 'r' && mode[1] == 'w')
    {
      *isReadable = 1;
      *isWritable = 1;
      return 1;
    }
  }
  return 0;
}

static void THDiskFile_synchronize(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  fflush(dfself->handle);
}

static void THDiskFile_seek(THFile *self, size_t position)
{
  THDiskFile *dfself = (THDiskFile*)(self);

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");

#ifdef _WIN32
  THArgCheck(position <= (size_t)LONG_MAX, 2, "position must be smaller than LONG_MAX");
  if(fseek(dfself->handle, (long)position, SEEK_SET) < 0)
#else
  THArgCheck(position <= (size_t)LLONG_MAX, 2, "position must be smaller than LLONG_MAX");
  if(fseeko(dfself->handle, (off_t)position, SEEK_SET) < 0)
#endif
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("unable to seek to position %zu", position);
  }
}

static void THDiskFile_seekEnd(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");

  if(fseek(dfself->handle, 0L, SEEK_END) < 0)
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("unable to seek at end of file");
  }
}

static size_t THDiskFile_position(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");

  long offset = ftell(dfself->handle);
  if (offset > -1)
      return (size_t)offset;
  else if(!dfself->file.isQuiet)
      THError("unable to obtain disk file offset (maybe a long overflow occured)");

  return 0;
}

static void THDiskFile_close(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  fclose(dfself->handle);
  dfself->handle = NULL;
}

/* Little and Big Endian */

static void THDiskFile_reverseMemory(void *dst, const void *src, size_t blockSize, size_t numBlocks)
{
  if(blockSize > 1)
  {
    size_t halfBlockSize = blockSize/2;
    char *charSrc = (char*)src;
    char *charDst = (char*)dst;
    size_t b, i;
    for(b = 0; b < numBlocks; b++)
    {
      for(i = 0; i < halfBlockSize; i++)
      {
        char z = charSrc[i];
        charDst[i] = charSrc[blockSize-1-i];
        charDst[blockSize-1-i] = z;
      }
      charSrc += blockSize;
      charDst += blockSize;
    }
  }
}

int THDiskFile_isLittleEndianCPU(void)
{
  int x = 7;
  char *ptr = (char *)&x;

  if(ptr[0] == 0)
    return 0;
  else
    return 1;
}

int THDiskFile_isBigEndianCPU(void)
{
  return(!THDiskFile_isLittleEndianCPU());
}

void THDiskFile_nativeEndianEncoding(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  dfself->isNativeEncoding = 1;
}

void THDiskFile_littleEndianEncoding(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  dfself->isNativeEncoding = THDiskFile_isLittleEndianCPU();
}

void THDiskFile_bigEndianEncoding(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  dfself->isNativeEncoding = !THDiskFile_isLittleEndianCPU();
}

/* End of Little and Big Endian Stuff */

void THDiskFile_longSize(THFile *self, int size)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(size == 0 || size == 4 || size == 8, 1, "Invalid long size specified");
  dfself->longSize = size;
}

void THDiskFile_noBuffer(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  if (setvbuf(dfself->handle, NULL, _IONBF, 0)) {
    THError("error: cannot disable buffer");
  }
}

static void THDiskFile_free(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  if(dfself->handle)
    fclose(dfself->handle);
  THFree(dfself->name);
  THFree(dfself);
}

/* READ_WRITE_METHODS(int, Bool, */
/*                    int value = 0; int ret = fscanf(file->handle, "%d", &value); array[i] = (value ? 1 : 0); if(ret <= 0) break; else result++, */
/*                    int value = (array[i] ? 1 : 0); nElemWritten = fprintf(file->handle, "%d", value), */
/*                    true) */

/* Note that we do a trick */
READ_WRITE_METHODS(unsigned char, Byte,
                   nread = fread(data, 1, n, dfself->handle); break,
                   nwrite = fwrite(data, 1, n, dfself->handle); break)

READ_WRITE_METHODS(char, Char,
                   nread = fread(data, 1, n, dfself->handle); break,
                   nwrite = fwrite(data, 1, n, dfself->handle); break)

READ_WRITE_METHODS(short, Short,
                   int ret = fscanf(dfself->handle, "%hd", &data[i]); if(ret <= 0) break; else nread++,
                   int ret = fprintf(dfself->handle, "%hd", data[i]); if(ret <= 0) break; else nwrite++)

READ_WRITE_METHODS(int, Int,
                   int ret = fscanf(dfself->handle, "%d", &data[i]); if(ret <= 0) break; else nread++,
                   int ret = fprintf(dfself->handle, "%d", data[i]); if(ret <= 0) break; else nwrite++)

/*READ_WRITE_METHODS(long, Long,
                   int ret = fscanf(dfself->handle, "%ld", &data[i]); if(ret <= 0) break; else nread++,
                   int ret = fprintf(dfself->handle, "%ld", data[i]); if(ret <= 0) break; else nwrite++)*/

READ_WRITE_METHODS(float, Float,
                   int ret = fscanf(dfself->handle, "%g", &data[i]); if(ret <= 0) break; else nread++,
                   int ret = fprintf(dfself->handle, "%.9g", data[i]); if(ret <= 0) break; else nwrite++)

READ_WRITE_METHODS(double, Double,
                   int ret = fscanf(dfself->handle, "%lg", &data[i]); if(ret <= 0) break; else nread++,
                   int ret = fprintf(dfself->handle, "%.17g", data[i]); if(ret <= 0) break; else nwrite++)


/* For Long we need to rewrite everything, because of the special management of longSize */
static size_t THDiskFile_readLong(THFile *self, long *data, size_t n)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  size_t nread = 0L;

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file");

  if(dfself->file.isBinary)
  {
    if(dfself->longSize == 0 || dfself->longSize == sizeof(long))
    {
      nread = fread__(data, sizeof(long), n, dfself->handle);
      if(!dfself->isNativeEncoding && (sizeof(long) > 1) && (nread > 0))
        THDiskFile_reverseMemory(data, data, sizeof(long), nread);
    } else if(dfself->longSize == 4)
    {
      int i;
      nread = fread__(data, 4, n, dfself->handle);
      if(!dfself->isNativeEncoding && (nread > 0))
        THDiskFile_reverseMemory(data, data, 4, nread);
      for(i = nread-1; i >= 0; i--)
        data[i] = ((int *)data)[i];
    }
    else /* if(dfself->longSize == 8) */
    {
      int i, big_endian = !THDiskFile_isLittleEndianCPU();
      long *buffer = THAlloc(8*n);
      nread = fread__(buffer, 8, n, dfself->handle);
      for(i = nread-1; i >= 0; i--)
        data[i] = buffer[2*i + big_endian];
      THFree(buffer);
      if(!dfself->isNativeEncoding && (nread > 0))
        THDiskFile_reverseMemory(data, data, 4, nread);
     }
  }
  else
  {
    size_t i;
    for(i = 0; i < n; i++)
    {
      int ret = fscanf(dfself->handle, "%ld", &data[i]); if(ret <= 0) break; else nread++;
    }
    if(dfself->file.isAutoSpacing && (n > 0))
    {
      int c = fgetc(dfself->handle);
      if( (c != '\n') && (c != EOF) )
        ungetc(c, dfself->handle);
    }
  }

  if(nread != n)
  {
    dfself->file.hasError = 1; /* shouldn't we put hasError to 0 all the time ? */
    if(!dfself->file.isQuiet)
      THError("read error: read %d blocks instead of %d", nread, n);
  }

  return nread;
}

static size_t THDiskFile_writeLong(THFile *self, long *data, size_t n)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  size_t nwrite = 0L;

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isWritable, 1, "attempt to write in a read-only file");

  if(dfself->file.isBinary)
  {
    if(dfself->longSize == 0 || dfself->longSize == sizeof(long))
    {
      if(dfself->isNativeEncoding)
      {
        nwrite = fwrite(data, sizeof(long), n, dfself->handle);
      }
      else
      {
        char *buffer = THAlloc(sizeof(long)*n);
        THDiskFile_reverseMemory(buffer, data, sizeof(long), n);
        nwrite = fwrite(buffer, sizeof(long), n, dfself->handle);
        THFree(buffer);
      }
    } else if(dfself->longSize == 4)
    {
      int i;
      int *buffer = THAlloc(4*n);
      for(i = 0; i < n; i++)
        buffer[i] = data[i];
      if(!dfself->isNativeEncoding)
        THDiskFile_reverseMemory(buffer, buffer, 4, n);
      nwrite = fwrite(buffer, 4, n, dfself->handle);
      THFree(buffer);
    }
    else /* if(dfself->longSize == 8) */
    {
      int i, big_endian = !THDiskFile_isLittleEndianCPU();
      long *buffer = THAlloc(8*n);
      for(i = 0; i < n; i++)
      {
        buffer[2*i + !big_endian] = 0;
        buffer[2*i + big_endian] = data[i];
      }
      if(!dfself->isNativeEncoding)
        THDiskFile_reverseMemory(buffer, buffer, 8, n);
      nwrite = fwrite(buffer, 8, n, dfself->handle);
      THFree(buffer);
    }
  }
  else
  {
    size_t i;
    for(i = 0; i < n; i++)
    {
      int ret = fprintf(dfself->handle, "%ld", data[i]); if(ret <= 0) break; else nwrite++;
      if( dfself->file.isAutoSpacing && (i < n-1) )
        fprintf(dfself->handle, " ");
    }
    if(dfself->file.isAutoSpacing && (n > 0))
      fprintf(dfself->handle, "\n");
  }

  if(nwrite != n)
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("write error: wrote %d blocks instead of %d", nwrite, n);
  }

  return nwrite;
}

static size_t THDiskFile_readString(THFile *self, const char *format, char **str_)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file");
  THArgCheck((strlen(format) >= 2 ? (format[0] == '*') && (format[1] == 'a' || format[1] == 'l') : 0), 2, "format must be '*a' or '*l'");

/* note: the string won't survive long, as it is copied into lua */
/* so 1024 is not that big... */
#define TBRS_BSZ 1024L

  if(format[1] == 'a')
  {
    char *p = THAlloc(TBRS_BSZ);
    size_t total = TBRS_BSZ;
    size_t pos = 0;

    for (;;)
    {
      if(total-pos == 0) /* we need more space! */
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      pos += fread(p+pos, 1, total-pos, dfself->handle);
      if (pos < total) /* eof? */
      {
        if(pos == 0)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
    }
  }
  else
  {
    char *p = THAlloc(TBRS_BSZ);
    size_t total = TBRS_BSZ;
    size_t pos = 0;
    size_t size;

    for (;;)
    {
      if(total-pos <= 1) /* we can only write '\0' in there! */
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      if (fgets(p+pos, total-pos, dfself->handle) == NULL) /* eof? */
      {
        if(pos == 0)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
      size = strlen(p+pos);
      if (size == 0 || (p+pos)[size-1] != '\n')
      {
        pos += size;
      }
      else
      {
        pos += size-1; /* do not include `eol' */
        *str_ = p;
        return pos;
      }
    }
  }

  *str_ = NULL;
  return 0;
}


static size_t THDiskFile_writeString(THFile *self, const char *str, size_t size)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  size_t nwrite;

  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isWritable, 1, "attempt to write in a read-only file");

  nwrite = fwrite(str, 1, size, dfself->handle);
  if(nwrite != size)
  {
    dfself->file.hasError = 1;
    if(!dfself->file.isQuiet)
      THError("write error: wrote %zu blocks instead of %zu", nwrite, size);
  }

  return nwrite;
}

THFile *THDiskFile_new(const char *name, const char *mode, int isQuiet)
{
  static struct THFileVTable vtable = {
    THDiskFile_isOpened,

    THDiskFile_readByte,
    THDiskFile_readChar,
    THDiskFile_readShort,
    THDiskFile_readInt,
    THDiskFile_readLong,
    THDiskFile_readFloat,
    THDiskFile_readDouble,
    THDiskFile_readString,

    THDiskFile_writeByte,
    THDiskFile_writeChar,
    THDiskFile_writeShort,
    THDiskFile_writeInt,
    THDiskFile_writeLong,
    THDiskFile_writeFloat,
    THDiskFile_writeDouble,
    THDiskFile_writeString,

    THDiskFile_synchronize,
    THDiskFile_seek,
    THDiskFile_seekEnd,
    THDiskFile_position,
    THDiskFile_close,
    THDiskFile_free
  };

  int isReadable;
  int isWritable;
  FILE *handle;
  THDiskFile *self;

  THArgCheck(THDiskFile_mode(mode, &isReadable, &isWritable), 2, "file mode should be 'r','w' or 'rw'");

  if( isReadable && isWritable )
  {
    handle = fopen(name, "r+b");
    if(!handle)
    {
      handle = fopen(name, "wb");
      if(handle)
      {
        fclose(handle);
        handle = fopen(name, "r+b");
      }
    }
  }
  else
    handle = fopen(name, (isReadable ? "rb" : "wb"));

  if(!handle)
  {
    if(isQuiet)
      return 0;
    else
      THError("cannot open <%s> in mode %c%c", name, (isReadable ? 'r' : ' '), (isWritable ? 'w' : ' '));
  }

  self = THAlloc(sizeof(THDiskFile));

  self->handle = handle;
  self->name = THAlloc(strlen(name)+1);
  strcpy(self->name, name);
  self->isNativeEncoding = 1;
  self->longSize = 0;

  self->file.vtable = &vtable;
  self->file.isQuiet = isQuiet;
  self->file.isReadable = isReadable;
  self->file.isWritable = isWritable;
  self->file.isBinary = 0;
  self->file.isAutoSpacing = 1;
  self->file.hasError = 0;

  return (THFile*)self;
}

/* PipeFile */

static int THPipeFile_mode(const char *mode, int *isReadable, int *isWritable)
{
  *isReadable = 0;
  *isWritable = 0;
  if(strlen(mode) == 1)
  {
    if(*mode == 'r')
    {
      *isReadable = 1;
      return 1;
    }
    else if(*mode == 'w')
    {
      *isWritable = 1;
      return 1;
    }
  }
  return 0;
}

static void THPipeFile_free(THFile *self)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  if(dfself->handle)
    pclose(dfself->handle);
  THFree(dfself->name);
  THFree(dfself);
}

THFile *THPipeFile_new(const char *name, const char *mode, int isQuiet)
{
  static struct THFileVTable vtable = {
    THDiskFile_isOpened,

    THDiskFile_readByte,
    THDiskFile_readChar,
    THDiskFile_readShort,
    THDiskFile_readInt,
    THDiskFile_readLong,
    THDiskFile_readFloat,
    THDiskFile_readDouble,
    THDiskFile_readString,

    THDiskFile_writeByte,
    THDiskFile_writeChar,
    THDiskFile_writeShort,
    THDiskFile_writeInt,
    THDiskFile_writeLong,
    THDiskFile_writeFloat,
    THDiskFile_writeDouble,
    THDiskFile_writeString,

    THDiskFile_synchronize,
    THDiskFile_seek,
    THDiskFile_seekEnd,
    THDiskFile_position,
    THDiskFile_close,
    THPipeFile_free
  };

  int isReadable;
  int isWritable;
  FILE *handle;
  THDiskFile *self;

  THArgCheck(THPipeFile_mode(mode, &isReadable, &isWritable), 2, "file mode should be 'r','w'");

#ifdef _WIN32
  handle = popen(name, (isReadable ? "rb" : "wb"));
#else
  handle = popen(name, (isReadable ? "r" : "w"));
#endif

  if(!handle)
  {
    if(isQuiet)
      return 0;
    else
      THError("cannot open <%s> in mode %c%c.  This might be because eg the executable doesn't exist, but it could also be because you are out of memory.", name, (isReadable ? 'r' : ' '), (isWritable ? 'w' : ' '));
  }

  self = THAlloc(sizeof(THDiskFile));

  self->handle = handle;
  self->name = THAlloc(strlen(name)+1);
  strcpy(self->name, name);
  self->isNativeEncoding = 1;
  self->longSize = 0;

  self->file.vtable = &vtable;
  self->file.isQuiet = isQuiet;
  self->file.isReadable = isReadable;
  self->file.isWritable = isWritable;
  self->file.isBinary = 0;
  self->file.isAutoSpacing = 1;
  self->file.hasError = 0;

  return (THFile*)self;
}
