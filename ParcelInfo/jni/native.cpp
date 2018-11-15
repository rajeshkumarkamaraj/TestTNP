
#include "com_trimble_outdoors_ndk_parcelinfo_ParcelUtils.h"
#include "com_trimble_outdoors_ndk_parcelinfo_ParcelUtils_Point.h"
#include "com_trimble_outdoors_ndk_parcelinfo_ParcelUtils_Ring.h"
#include "com_trimble_outdoors_ndk_parcelinfo_ParcelUtils_Polygon.h"
#include "com_trimble_outdoors_ndk_parcelinfo_ParcelUtils_ParcelInfo.h"
/* Header for class com_trimble_ndk_tnp_NavtiveCalls */


#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<stack>
#include<string>
#include <android/log.h>

using namespace std;


#define  LOG_DATA_NDK

#define  LOG_TAG    "TNP"
#define  DEBUG_TAG	"TNP_DEBUG"


#ifdef LOG_DATA_NDK
#define  LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,DEBUG_TAG,__VA_ARGS__)
#endif


jfloat lat,lon;
unsigned long cPARCEL_ID;
string	cAPN;			// ***
string cAPN2;			// ***
string	cOWNER;			// ***
string	cADDR;			// ***
string	cCITY;			// *** added on second pass
string	cZIP;

jstring apn_str, apn2_str, owner_str, addr_str, city_str, zip_str;

static JavaVM *jvm=NULL;

char fp[50]="/storage/emulated/0/writee";
typedef unsigned long long    UINT64, *PUINT64;
typedef unsigned long       DWORD;
#define MAKEID(a,b,c,d)	(((DWORD)(a) << 24) | ((DWORD)(b) << 16) |	\
((DWORD)(c) <<  8) | ((DWORD)(d)      ))
static const int kType = MAKEID('S', 'D', 'B', 'X');
static const int kMajor = 1;
static const int kMinor = 0;
typedef  long LONG_PTR;
typedef LONG_PTR LPARAM;
namespace geos {

    typedef int64_t	geosID_t;
    template <typename _T> class basic_id {
        public:
        basic_id() : m_id(0)
        {

        }
        basic_id(_T id) : m_id(id)
        {

        }
        _T getid() const

        {
            return m_id;
        }
        private:

        _T			m_id;
    };

};
class CSDBFile {
    public:
    CSDBFile() : m_file(NULL) {}

    ~CSDBFile()
    {
        close();
    }

    bool open(std::string fName, std::string mode)
    {
        //			m_file = fopen(fName.c_str(), mode.c_str());
        //			return (m_file ? true : false);

    	LOGI("OPEN FILE ");

        //return fopen_s(&m_file, fName.c_str(), mode.c_str()) == 0;


    	m_file=fopen(fName.c_str(),"r");
    	LOGI("%s opened",fName.c_str());
    	LOGI("%d open status",(m_file != 0));
       return m_file != 0;
    }

    void close()
    {
        if (m_file)
        fclose(m_file);
        m_file = NULL;
    }

    void read(void * buffer, size_t bytes)
    {
    	LOGI("CSDFILE read");




        if (m_file == NULL)

        {

        }




        if (fread(buffer, 1, bytes, m_file) != bytes)
        {
        	LOGI("buffer is null");
        }

        LOGI("buffer is read");
    }

    void write(void * buffer, size_t bytes)
    {
        if (m_file == NULL)
        {
        }

        if (fwrite(buffer, 1, bytes, m_file) != bytes)
        {
        }
    }

    private:
    FILE* m_file;
};

template <typename _ID = int32_t> class CSDBHeader {
    public:

    CSDBHeader() : m_type(kType), m_major(kMajor), m_minor(kMinor), m_size(0), m_id(0)
    {
    }

    void read(CSDBFile& file)
    {


    	LOGI("CSDBHEADER read");
        file.read(&m_type, sizeof(m_type));
        file.read(&m_major, sizeof(m_major));
        file.read(&m_minor, sizeof(m_minor));
        file.read(&m_size, sizeof(m_size));
        file.read(&m_id, sizeof(m_id));

        LOGI("CSDBHEADER finish reading");

        if (m_type != kType)
        {
        }
    }

    void write(CSDBFile& file)
    {
        file.write(&m_type, sizeof(m_type));
        file.write(&m_major, sizeof(m_major));
        file.write(&m_minor, sizeof(m_minor));
        file.write(&m_size, sizeof(m_size));
        file.write(&m_id, sizeof(m_id));
    }

    DWORD size()
    {
        return m_size;
    }

    void set_size(DWORD size)
    {
        m_size = size;
    }

    DWORD major()
    {
        return m_major;
    }

    void set_major(DWORD major)
    {
        m_major = major;
    }

    DWORD minor()
    {
        return m_minor;
    }

    void set_minor(DWORD minor)
    {
        m_minor = minor;
    }

    _ID id()
    {
        return m_id;
    }

    void set_id(_ID id)
    {
        m_id = id;
    }

    private:
    DWORD m_type;
    DWORD m_major;
    DWORD m_minor;
    DWORD m_size;
    _ID	  m_id;
};

template <typename _T> class CSDB_Field {
    public:
    CSDB_Field()
    {
        //memset(&m_value, 0, sizeof(m_value));
    }

    CSDB_Field<_T>& operator=(_T& rhs)
    {
        //memcpy(&m_value, &rhs, sizeof(m_value));
    }

    protected:
    _T m_value;
};
template < std::size_t _N> class CSDB_Field<const char[_N]> {
    public:
    CSDB_Field()
    {
        //memset(&m_value, 0, sizeof(m_value));
    }

    CSDB_Field<const char[_N]>& operator=(const char rhs[_N])
    {
        //memcpy(&m_value, rhs, sizeof(m_value));
    }

    protected:
    char m_value[_N];
};
template <size_t _S> class CSDB_StrN : public CSDB_Field<char[_S]> {
    public:
    CSDB_StrN& operator=(const char rhs[_S])
    {
       // memcpy(m_value, rhs, sizeof(m_value));
        return *this;
    }


  /*  operator LPARAM()
    {
        return (LPARAM)m_value;
    }

    operator std::string()
    {
        return (std::string)m_value;
    }

    operator char*()
    {
        return (char*)m_value;
    }

    CSDB_StrN& operator=(std::string& rhs)
    {
        strcpy_s(m_value, rhs.c_str());
        return *this;
    }*/
};

template <size_t _S> class CSDB_ObfStrN : public CSDB_Field<char[_S]> {
    public:
  /*  CSDB_ObfStrN& operator=(const char rhs[_S])
    {
        for (int i = 0; i < sizeof(m_value); ++i) {
            if (rhs[i])
            m_value[i] = ~rhs[i];
            else
            m_value[i] = 0;
        }

        return *this;
    }

    operator std::string()
    {
        string s;

        for (int i = 0; i < sizeof(m_value); ++i)
        if (m_value[i]) {
            s += ~m_value[i];
        }
        else {
            //					s += (char)0;
            break;
        }

        return s;
    }

    CSDB_ObfStrN& operator=(std::string& rhs)
    {
        for (int i = 0; i < rhs.length(); ++i)
        m_value[i] = ~rhs[i];
        m_value[rhs.length()] = 0;

        return *this;
    }*/
};


class CSDB_DWORD : public CSDB_Field<DWORD> {
    public:
  /*  CSDB_DWORD& operator=(DWORD rhs)
    {
       // memcpy(&m_value, &rhs, sizeof(m_value));
        return *this;
    }

    operator DWORD()
    {
        return m_value;
    }*/
};
template <typename _Tp> class CSDB_Fundamental : public CSDB_Field<_Tp> {
    public:
   /* CSDB_Fundamental& operator=(_Tp rhs)
    {
        m_value = rhs;
        return *this;
    }

    operator _Tp()
    {
        return m_value;
    }*/
};

template <typename _T, typename _ID = int32_t, typename _IDX = int32_t> class CSDB {
    public:
    /* ID and INDEX types */
    typedef _ID		DBID_t;
    typedef _IDX	DBIndex_t;

    /* map type */
    typedef std::map<DBID_t, DBIndex_t>	map_t;

    /* storage type */
    typedef std::vector<_T>				storage_t;

    /* index type */
    typedef struct {
        DBID_t		id;
        DBIndex_t	index;
    } map_idx_t;

    class iterator {
        public:
        typedef iterator					self_type;
        typedef _T							value_type;
        typedef _T&							reference;
        typedef _T*							pointer;
        typedef std::forward_iterator_tag	iterator_category;
        typedef int							difference_type;

        // for begin()/end()
        iterator(storage_t* storage, typename map_t::iterator it) : m_storage(storage), m_iterator(it)
        {
        }

        iterator(const iterator& other)
        {
            m_storage = other.m_storage;
            m_iterator = other.m_iterator;
        }
        private:
        storage_t*					m_storage;
        typename map_t::iterator	m_iterator;
    };

    typedef iterator const_iterator;

    CSDB() : m_mxID(0)
    {
    }

    void setID(DBID_t id)
    {
        m_mxID = id;
    }

    iterator operator[](DBID_t id)
    {
        return find(id);
    }

    iterator find(DBID_t id)
    {
        return iterator(&m_storage, m_map.find(id));
    }
    bool load(std::string fName)
    {
        /* open */
        CSDBFile file;
        if (!file.open(fName, "rb"))
        return false;


        /* read header */
        m_header.read(file);



        /* create temp vector for reading index */
        std::vector<map_idx_t> index;
        index.resize(m_header.size());

        /* read index */
        if (m_header.size())
        file.read(&index[0], m_header.size() * sizeof(map_idx_t));

        /*
        for (vector<map_idx_t>::iterator it = index.begin(); it != index.end(); ++it)
        m_map[it->id] = it->index;*/

        /* allocate vector and read */
        m_storage.resize(m_header.size());

        if (m_header.size())
        file.read(&m_storage[0], m_header.size() * sizeof(_T));

        /* reset id */
        setID(m_header.id());

        return true;
    }
    bool pload(std::string fName)
    {
        /* open */

        CSDBFile file;
        if (!file.open(fName, "rb"))
        return false;




        /* read header */
        m_header.read(file);


        LOGI("HEADER IS READ");


        /* create temp vector for reading index */
        std::vector<map_idx_t> index;
        index.resize(m_header.size());

        /* read index */
        if (m_header.size())
        file.read(&index[0], m_header.size() * sizeof(map_idx_t));

        LOGI("Index IS READ");


        /* allocate vector and read */
        m_storage.resize(m_header.size());

        if (m_header.size())
        file.read(&m_storage[0], m_header.size() * sizeof(_T));

        LOGI("Storage IS READ");

        /* reset id */
        setID(m_header.id());
        DWORD i;
        DWORD c = m_header.size();



        LOGI("Count is  %ld",c);



        FILE * pFileTXT;
                pFileTXT = fopen (fp,"a");
         float latt,lonn;

         JNIEnv *env;
         	(jvm)->AttachCurrentThread( &env, NULL);

               for(i=0;i<c;i++)
               {
                      latt=(float)m_storage[i].LATITUDE;
                      lonn=(float)m_storage[i].LONGITUDE;

             //      __android_log_print(ANDROID_LOG_INFO,"TNP","%d   %f   %f",i,m_storage[i].LONGITUDE,m_storage[i].LATITUDE);
                   if((lonn==lon) && (latt==lat))
                   {
                    /*fprintf (pFileTXT, "NO:  %lu\n",i );
                    fprintf (pFileTXT, "Parcel id:  %lu\n",m_storage[i].PARCEL_ID);
                    fprintf (pFileTXT, "APN:  %s\n",m_storage[i].APN);
      				fprintf (pFileTXT, "APN2:  %s\n",m_storage[i].APN2);
      				fprintf (pFileTXT, "OWNER:  %s\n",m_storage[i].OWNER);
      	            fprintf (pFileTXT, "ADDRESS:  %s\n",m_storage[i].ADDR);
      	      	    fprintf (pFileTXT, "CITY:  %s\n",m_storage[i].CITY);
      	      	    fprintf (pFileTXT, "ZIP:  %s\n",m_storage[i].ZIP);
      	      	    fprintf (pFileTXT, "LONGITUDE:  %f",m_storage[i].LONGITUDE);
      	     		fprintf (pFileTXT, "LATITUDE:  %f\n",m_storage[i].LATITUDE);*/

      	     	// cPARCEL_ID=m_storage[i].PARCEL_ID;
      	     	      apn_str = env->NewStringUTF(m_storage[i].APN);
      	     	      apn2_str = env->NewStringUTF(m_storage[i].APN2);
      	     	      owner_str = env->NewStringUTF("error");
      	     	      addr_str = env->NewStringUTF("error");
      	     	      city_str = env->NewStringUTF(m_storage[i].CITY);
      	     	      zip_str = env->NewStringUTF(m_storage[i].ZIP);

      	     		//cAPN=(string)(m_storage[i].APN);

                   }
                   else
                   {


                   }
               }
                		fclose (pFileTXT);




        return true;
    }
    iterator begin()
    {
        return iterator(&m_storage, m_map.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(&m_storage, m_map.begin());
    }

    iterator end()
    {
        return iterator(&m_storage, m_map.end());
    }

    const_iterator end() const
    {
        return const_iterator(&m_storage, m_map.end());
    }

    size_t size()
    {
        return m_map.size();
    }

    private:
    CSDBHeader<_ID>	m_header;
    DBID_t			m_mxID;
    map_t			m_map;
    storage_t		m_storage;
};

struct StateRecord {
    CSDB_DWORD					fipspart;
    CSDB_Fundamental<UINT64>	datetime;
    CSDB_Fundamental<UINT64>	size;
};
struct ParcelRecord {
    CSDB_DWORD		PARCEL_ID;		// ***

    char	APN[50];			// ***
    char	APN2[50];			// ***
    char	OWNER[50];			// ***
    char	ADDR[100];			// ***
    char	CITY[50];			// *** added on second pass
    char	ZIP[5];			// *** added on second pass
    //CSDB_Fundamental<float>		LONGITUDE;		// point
    //CSDB_Fundamental<float>		LATITUDE;		// point
    float LONGITUDE;
    float LATITUDE;
};
/*
 struct ParcelRecord {
	CSDB_DWORD		PARCEL_ID;		// ***

	CSDB_StrN<50>	APN;			// ***
	CSDB_StrN<50>	APN2;			// ***
	CSDB_StrN<50>	OWNER;			// ***
	CSDB_StrN<100>	ADDR;			// ***
	CSDB_StrN<50>	CITY;			// *** added on second pass
	CSDB_StrN<5>	ZIP;			// *** added on second pass
	CSDB_Fundamental<float>		LONGITUDE;		// point
	CSDB_Fundamental<float>		LATITUDE;		// point
 };*/

typedef CSDB<StateRecord, geos::geosID_t, int32_t>		sdb_t;

typedef CSDB<ParcelRecord, geos::geosID_t, int32_t>		psdb_t;








JNIEXPORT jobject JNICALL Java_com_trimble_outdoors_ndk_parcelinfo_ParcelUtils_getParcelInfo
  (JNIEnv *env, jobject thisobj, jstring jStringPath, jobject point)
{


		 		int len = (env)->GetStringLength(jStringPath);
		 		char outbuf[len];
		 		(env)->GetStringUTFRegion(jStringPath, 0, len, outbuf);
		 		outbuf[len]='\0';
		 		LOGI( " len=%d", len);
		 		LOGI( "jStringPath :%s",outbuf);
		 		jclass point_class=env->GetObjectClass(point);
		 		jfieldID point_lat=env->GetFieldID(point_class,"lat","F");
		 		jfieldID point_lon=env->GetFieldID(point_class,"lon","F");

		 		lat=env->GetFloatField(point,point_lat);
		 		lon=env->GetFloatField(point,point_lon);



		 		psdb_t m_psdb;

		 		m_psdb.pload(outbuf);

		 		  LOGI("OVVEEERRR     ");

		 		   jclass parcel_info_class=(env)->FindClass("com/trimble/outdoors/ndk/parcelinfo/ParcelUtils$ParcelInfo");

                  //jstring apn_str, apn2_str, owner_str, addr_str, city_str, zip_str;

                  jmethodID initMethod = env->GetMethodID(parcel_info_class, "<init>", "()V");
                  jobject jParcelInfo = env->AllocObject (parcel_info_class);



                  LOGI("objectttt   ");
		 		//jfieldID japn = env->GetFieldID (parcel_info_class,"apn" , "J");
		 		//env->SetLongField (jParcelInfo, japn, apn_str);

                  jfieldID japn = env->GetFieldID (parcel_info_class, "apn", "Ljava/lang/String;");
		 		     //strrr=env->NewStringUTF(cAPN.c_str());
                  env->SetObjectField(jParcelInfo, japn, apn_str);


                  jfieldID japn2 = env->GetFieldID (parcel_info_class, "apn2", "Ljava/lang/String;");
		 		    //strrr2=env->NewStringUTF(cAPN2.c_str());
		 		  env->SetObjectField(jParcelInfo, japn2, apn2_str);

		 		  jfieldID jowner = env->GetFieldID (parcel_info_class, "owner", "Ljava/lang/String;");
		 		    //strrr3=env->NewStringUTF(cOWNER.c_str());
		 		  env->SetObjectField(jParcelInfo, jowner, owner_str);

		 		  jfieldID jaddr = env->GetFieldID (parcel_info_class, "address" , "Ljava/lang/String;");
		 		    //strrr4=env->NewStringUTF(cADDR.c_str());
		 		  env->SetObjectField(jParcelInfo, jaddr, addr_str);

		 		  jfieldID jcity = env->GetFieldID (parcel_info_class, "city", "Ljava/lang/String;");
		 		    //strrr5=env->NewStringUTF(cCITY.c_str());
		 		  env->SetObjectField(jParcelInfo, jcity, city_str);

		 		  jfieldID jzip = env->GetFieldID (parcel_info_class, "zip", "Ljava/lang/String;");
		 		    //strrr6=env->NewStringUTF(cZIP.c_str());
		 		  env->SetObjectField(jParcelInfo, jzip, zip_str);




		 		 /*  jclass clss=(env)->FindClass("com/trimble/ndk/tnp/ParcelUtils$PointD");
		 		     jobject obj1 = env->AllocObject (clss);

		 		     jfieldID latt = env->GetFieldID (clss,"lat" , "F");
		 		     env->SetFloatField (obj1, latt, clat);
		 		     jfieldID lonn = env->GetFieldID (clss,"lon" , "F");
		 		     env->SetFloatField (obj1, lonn, clon);



		 		     jfieldID pid=env->GetFieldID(pclss,"p","com/trimble/ndk/tnp/LParcelUtils$PointD;");
		 		        env->SetObjectField(obj,pid,obj1);*/

		 		       //jobject obj = env->NewObject(pclss, initMethod,strrr,strrr2,strrr3,strrr4,strrr5,strrr6,clon,clat);
		 		       LOGI("OVEEEEEEEEtttt   ");
		 		     return jParcelInfo;
}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

	JNIEnv *env;

	LOGI( "tnp Jni onload");

	if ((vm)->GetEnv( (void **)&env, JNI_VERSION_1_6)) {
		return JNI_ERR;
	}
	jvm=vm;
	return JNI_VERSION_1_6;
}
