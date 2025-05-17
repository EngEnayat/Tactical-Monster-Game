/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 6.8.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#ifdef _MSC_VER
// disable informational message "function ... selected for automatic inline expansion"
#pragma warning (disable: 4711)
#endif

static const unsigned char qt_resource_data[] = {
  // grid1.txt
  0x0,0x0,0x0,0x4a,
  0x28,
  0xb5,0x2f,0xfd,0x60,0x49,0x0,0x5,0x2,0x0,0x12,0x42,0x6,0xb,0xe0,0xe9,0x68,
  0x60,0x71,0xee,0xee,0x7a,0xa,0x7d,0x9d,0x3f,0x8,0x48,0x49,0x8c,0x8f,0xf4,0x54,
  0x4b,0x1f,0xe3,0xdf,0x1e,0x12,0xa0,0x80,0x6e,0xda,0x16,0x3,0x40,0x2d,0x6c,0x1b,
  0x54,0x7d,0x4d,0x72,0x84,0x8b,0x7b,0x4d,0xc5,0x63,0xe0,0xfd,0x43,0x2f,0xbd,0x6f,
  0x80,0xb5,0x47,0x17,0xf9,0x21,0xa9,0xff,0xe,
  
};

static const unsigned char qt_resource_name[] = {
  // grids
  0x0,0x5,
  0x0,0x6e,0x8f,0xb3,
  0x0,0x67,
  0x0,0x72,0x0,0x69,0x0,0x64,0x0,0x73,
    // grid1.txt
  0x0,0x9,
  0xf,0x74,0x86,0xf4,
  0x0,0x67,
  0x0,0x72,0x0,0x69,0x0,0x64,0x0,0x31,0x0,0x2e,0x0,0x74,0x0,0x78,0x0,0x74,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/grids
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x2,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  // :/grids/grid1.txt
  0x0,0x0,0x0,0x10,0x0,0x4,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,
0x0,0x0,0x1,0x96,0x62,0x31,0x9a,0x12,

};

#ifdef QT_NAMESPACE
#  define QT_RCC_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::name
#  define QT_RCC_MANGLE_NAMESPACE0(x) x
#  define QT_RCC_MANGLE_NAMESPACE1(a, b) a##_##b
#  define QT_RCC_MANGLE_NAMESPACE2(a, b) QT_RCC_MANGLE_NAMESPACE1(a,b)
#  define QT_RCC_MANGLE_NAMESPACE(name) QT_RCC_MANGLE_NAMESPACE2( \
        QT_RCC_MANGLE_NAMESPACE0(name), QT_RCC_MANGLE_NAMESPACE0(QT_NAMESPACE))
#else
#   define QT_RCC_PREPEND_NAMESPACE(name) name
#   define QT_RCC_MANGLE_NAMESPACE(name) name
#endif

#if defined(QT_INLINE_NAMESPACE)
inline namespace QT_NAMESPACE {
#elif defined(QT_NAMESPACE)
namespace QT_NAMESPACE {
#endif

bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
bool qUnregisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);

#if defined(__ELF__) || defined(__APPLE__)
static inline unsigned char qResourceFeatureZstd()
{
    extern const unsigned char qt_resourceFeatureZstd;
    return qt_resourceFeatureZstd;
}
#else
unsigned char qResourceFeatureZstd();
#endif

#ifdef QT_NAMESPACE
}
#endif

int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)()
{
    int version = 3;
    QT_RCC_PREPEND_NAMESPACE(qRegisterResourceData)
        (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)();
int QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)()
{
    int version = 3;
    version += QT_RCC_PREPEND_NAMESPACE(qResourceFeatureZstd());
    QT_RCC_PREPEND_NAMESPACE(qUnregisterResourceData)
       (version, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

#ifdef __clang__
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif

namespace {
   struct initializer {
       initializer() { QT_RCC_MANGLE_NAMESPACE(qInitResources_resources)(); }
       ~initializer() { QT_RCC_MANGLE_NAMESPACE(qCleanupResources_resources)(); }
   } dummy;
}

#ifdef __clang__
#   pragma clang diagnostic pop
#endif
