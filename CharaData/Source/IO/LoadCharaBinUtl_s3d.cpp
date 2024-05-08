//=================================================================================================
//
// LoadCharaBinUtl_s3d ソースファイル
//
//=================================================================================================
#include "LoadCharaBinUtl_s3d.h"
//#include <codecvt>

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinUtl_s3d::LoadCharaBinUtl_s3d ()
	{
		::setlocale ( LC_ALL, "japanese" );
	}


	//-----------------------------------------------------------------------
	tstring LoadCharaBinUtl_s3d::LoadText ( P_Byte buf, UINT & pos )
	{
#if 0
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8

		//文字列に変換
		std::unique_ptr < char [] > pch = std::make_unique < char [] > ( length + 1 );
		::memccpy ( pch.get (), buf.get(), 0, length );

		//UTF8 -> wstring
		std::string str ( pch.get() + pos, length );
		std::wstring_convert < std::codecvt_utf8_utf16 < wchar_t > > converter;
		tstring tstr = converter.from_bytes ( str );

		//位置を更新
		pos += length;

		//取得した名前を返す
		return tstr ;
#endif // 0
		tstring tstr;
		return tstr;
	}


	s3d::String LoadCharaBinUtl_s3d::LoadString ( P_Byte buf, UINT & pos )
	{
		//名前のサイズ
		byte length = buf [ pos ++ ];	//Encoding.UTF8

		//対象文字列
		s3d::String text;
		text.resize ( length );

		//文字列に変換
		::memccpy ( text.data (), buf.get(), 0, length );

		//位置を更新
		pos += length;

		//取得した名前を返す
		return text;
	}


	bool LoadCharaBinUtl_s3d::LoadBool ( P_Byte buf, UINT & pos )
	{
		//bool値も1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];	//1  or 0
		return (bool)b;
	}

	byte LoadCharaBinUtl_s3d::LoadByte ( P_Byte buf, UINT & pos )
	{
		//1バイト読み込んでポインタを進め、値を返す
		byte b = buf [ pos ++ ];
		return b;
	}

	int LoadCharaBinUtl_s3d::LoadInt ( P_Byte buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		int i = 0;
		rsize_t size = sizeof ( int );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT)size;
		return i;
	}

	UINT LoadCharaBinUtl_s3d::LoadUInt ( P_Byte buf, UINT & pos )
	{
		//リトルエンディアン読込 (byte[])0x67 0x45 0x23 0x01 -> (UINT)0x01234567
		UINT i = 0;
		rsize_t size = sizeof ( UINT );
		::memcpy_s ( &i, size, buf.get () + pos, size );
		pos += (UINT)size;
		return i;
	}


	VEC2 LoadCharaBinUtl_s3d::LoadVec2 ( P_Byte buf, UINT & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( (float)pos_x, (float)pos_y );
	}

	//intで読んだ値を10.fで割る(0.1f掛ける)
	VEC2 LoadCharaBinUtl_s3d::LoadVec2_Dev10F ( P_Byte buf, UINT & pos )
	{
		int pos_x = LoadInt ( std::move ( buf ), pos );
		int pos_y = LoadInt ( std::move ( buf ), pos );
		return VEC2 ( 0.1f * pos_x, 0.1f * pos_y );
	}


	RECT LoadCharaBinUtl_s3d::LoadRect ( P_Byte buf, UINT & pos )
	{
		//繝ェ繝医Ν繧ィ繝ウ繝ぅ繧「繝ウ隱ュ霎シ (byte[])0x67 0x45 0x23 0x01 -> (int)0x01234567
		RECT rect = { 0 };
		rsize_t size = sizeof ( RECT );
		::memcpy_s ( &rect, size, buf.get () + pos, size );
		pos += (UINT)size;
		return rect;
	}

	
	void LoadCharaBinUtl_s3d::LoadListRect ( P_Byte buf, UINT & pos, PV_RECT pvRect )
	{
		UINT n = buf [ pos ++ ];
		pvRect->clear ();
		pvRect->resize ( n );
		for ( UINT i = 0; i < n; ++ i )
		{
			( *pvRect ) [ i ] = LoadRect ( std::move ( buf ), pos );
		}
	}


	L_UINT LoadCharaBinUtl_s3d::LoadAryUint ( P_Byte buf, UINT & pos, UINT & refLength )
	{
		refLength = buf [ pos ++ ];

		std::unique_ptr < UINT [] > ary_uint = std::make_unique < UINT [] > ( refLength );
		for ( UINT i = 0; i < refLength; ++ i )
		{
			ary_uint [ i ] = (UINT)buf [ pos ++ ];
		}

		return std::move ( ary_uint );
	}


	void LoadCharaBinUtl_s3d::LoadAryUint ( P_Byte buf, UINT & pos, V_UINT & refAryUint )
	{
		UINT size = LoadUInt ( std::move ( buf ), pos );
		refAryUint.resize ( size );
		for ( UINT i = 0; i < size; ++ i )
		{
			refAryUint [ i ] = LoadUInt ( std::move ( buf ), pos );
		}
	}


}	//namespace GAME

