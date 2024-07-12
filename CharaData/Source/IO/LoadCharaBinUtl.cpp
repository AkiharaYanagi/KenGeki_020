//=================================================================================================
//
// LoadCharaBinUtl ソースファイル
//
//=================================================================================================
#include "LoadCharaBinUtl.h"
#include <codecvt>

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinUtl::LoadCharaBinUtl ()
	{
		::setlocale ( LC_ALL, "japanese" );
	}

#if 0
	//-----------------------------------------------------------------------
	tstring LoadCharaBinUtl::LoadText ( CUPR_BYTE buf, UINT & pos )
	{
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8

		//		unique_ptr < char [] > arypChar = make_unique < char [] > ( length + 1 );
		//		memcpy_s ( arypChar.get(), length ,buf, length );

		//		unique_ptr < TCHAR [] >  tbuf = make_unique < TCHAR [] > ( length + 1 );
		//		size_t _PptNumOfCharConverted = 0;
		//		errno_t err = ::mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get (), length + 1, arypChar.get (), _TRUNCATE );

		//UTF8 -> wstring
		std::string str ( (char*)buf.get() + pos, length );
		std::wstring_convert < std::codecvt_utf8_utf16 < wchar_t > > converter;
		tstring tstr = converter.from_bytes ( str );

		//位置を更新
		pos += length;

		//取得した名前を返す
		return tstr ;
	}
#endif // 0

	//-----------------------------------------------------------------------
	s3d::String LoadCharaBinUtl::LoadS3dString ( CUPR_BYTE buf, UINT & pos )
	{
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8
//		byte length = buf [ pos ];	//Encoding.UTF8

		//位置
//		char* index = (char*)buf.get() + pos;

		//UTF8 -> wstring
		// MultiByte -> WChar
#if 0
		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( length );
		size_t sizebuf = strlen ( index ) + 1;
		size_t n = 0;
		::mbstowcs_s ( & n, tbuf.get(), sizebuf, index, _TRUNCATE );
		tstring tstr ( tbuf.get() );

		std::string str ( index, length );
		s3d::String s3dStr = Unicode::Widen ( str );
#endif // 0

#if 0
		int tsize = ::MultiByteToWideChar ( CP_UTF8, 0, index, length, nullptr, 0 );
		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( tsize + 1 );
		::MultiByteToWideChar ( CP_UTF8, 0, index, length, tbuf.get(), tsize + 1 );
		tstring tstr ( tbuf.get() );
		s3d::String s3dStr = Unicode::FromWstring ( tstr );
#endif // 0


//		s3d::String s3dStr = Unicode::FromUTF8 ( index );

		std::string str ( (char*)buf.get() + pos, length );
		s3d::String s3dStr = Unicode::FromUTF8 ( str );


		//位置を更新
		pos += length;
//		size_t size_byte = s3dStr.size_bytes ();
//		pos += size_byte;

		//取得した名前を返す
		return s3dStr;
	}


	bool LoadCharaBinUtl::LoadBool ( CUPR_BYTE buf, UINT & pos )
	{
		//bool値も1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];	//1  or 0
		return (bool)b;
	}

	byte LoadCharaBinUtl::LoadByte ( CUPR_BYTE buf, UINT & pos )
	{
		//1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];
		return b;
	}

	int LoadCharaBinUtl::LoadInt ( CUPR_BYTE buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		int i = 0;
		rsize_t size = sizeof ( int );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT)size;
		return i;
	}

	UINT LoadCharaBinUtl::LoadUInt ( CUPR_BYTE buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT)0x01234567
		UINT i = 0;
		rsize_t size = sizeof ( UINT );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT)size;
		return i;
	}


	VEC2 LoadCharaBinUtl::LoadVec2 ( CUPR_BYTE buf, UINT & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( (float)pos_x, (float)pos_y );
	}

	//intで読んだ値を10.fで割る(0.1f掛ける)
	VEC2 LoadCharaBinUtl::LoadVec2_Dev10F ( CUPR_BYTE buf, UINT & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( 0.1f * pos_x, 0.1f * pos_y );
	}


	RECT LoadCharaBinUtl::LoadRect ( CUPR_BYTE buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT)0x01234567
		RECT rect = { 0 };
		rsize_t size = sizeof ( RECT );
		::memcpy_s ( &rect, size, buf.get () + pos, size );
		pos += (UINT)size;
		return rect;
	}

	
	void LoadCharaBinUtl::LoadListRect ( CUPR_BYTE buf, UINT & pos, PV_RECT pvRect )
	{
		UINT n = buf [ pos ++ ];
		pvRect->clear ();
		pvRect->resize ( n );
		for ( UINT i = 0; i < n; ++ i )
		{
			( *pvRect ) [ i ] = LoadRect ( std::move ( buf ), pos );
		}
	}


	L_UINT LoadCharaBinUtl::LoadAryUint ( CUPR_BYTE buf, UINT & pos, UINT & refLength )
	{
		refLength = buf [ pos ++ ];

		std::unique_ptr < UINT [] > ary_uint = std::make_unique < UINT [] > ( refLength );
		for ( UINT i = 0; i < refLength; ++ i )
		{
			ary_uint [ i ] = (UINT)buf [ pos ++ ];
		}

		return std::move ( ary_uint );
	}


	void LoadCharaBinUtl::LoadAryUint ( CUPR_BYTE buf, UINT & pos, V_UINT & refAryUint )
	{
		UINT size = LoadUInt ( std::move ( buf ), pos );
		refAryUint.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			refAryUint [ i ] = LoadUInt ( std::move ( buf ), pos );
		}
	}


}	//namespace GAME

