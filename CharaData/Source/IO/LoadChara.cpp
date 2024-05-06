//=================================================================================================
//
// LoadChara ソースファイル
//
//=================================================================================================
#include "LoadChara.h"
//#include "Branch.h"	//ActionとCommandを扱うためChara.hとは独立


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		スクリプトとイメージリストを保存したキャラデータ ".dat"ファイル から、Charaを読み込む
	//==================================================================================
	LoadChara::LoadChara ( const tstring & filename, Chara & chara ) 
	{
		try
		{
			_Load ( filename, chara );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadChara.\n") );
		}
	}

	//----------------------------------
	//	デストラクタ
	//----------------------------------
	LoadChara::~LoadChara ()
	{
	}


	//------------------------------------------
	//	try用実行関数
	//------------------------------------------
	void LoadChara::_Load ( const tstring & filename, Chara & chara )
	{


		DWORD startTime = ::timeGetTime ();




		//初期化
		chara.Reset ();

		//拡張子を.datかどうか確認
		const int NX = 4;	//拡張子の文字数
		if ( 0 != filename.compare ( filename.size() - NX, NX, _T(".dat"), 0, NX ) )
		{
			throw _T("拡張子エラー\n"); 
		}

		//------------------------------------------
		//@info  tifstream ではなく ifstream
		//		バイナリファイルなのでchar型で扱う
		//------------------------------------------

		//---------------------------------------------------------------------
		//ファイルストリーム開始
		std::ifstream ifstrm ( filename.c_str(), std::ios::binary );

		//ファイルが存在しないとき何もしない
		if ( ifstrm.fail () ) { throw _T("ファイルが存在しません。"); } 

		//キャラデータ形式のバージョン[uint]
		UINT version = 0;	//読込用
		ifstrm.read ( (char*)& version, sizeof ( UINT ) );
		if ( CHARA_VERSION != version ) { throw _T("キャラアーカイブのバージョンが異なります。"); } 

		//---------------------------------------------------------------------
		//スクリプト部のサイズ
		UINT scriptSize = 0;
		ifstrm.read ( (char*)& scriptSize, sizeof ( UINT ) );

		//一時読込
		char* scriptBuf = new char [ scriptSize ];
		ifstrm.read ( scriptBuf, scriptSize );




		DWORD scriptRead_Time = ::timeGetTime ();





		//Documentを生成
		Document document ( scriptBuf, scriptSize );




		DWORD Document_Time = ::timeGetTime ();



		//一時読込の破棄
		delete[] scriptBuf;

		//キャラデータに変換
		m_func._DocumentToChara ( document, chara );




		DWORD DtoC_Time = ::timeGetTime ();



		//---------------------------------------------------------------------
		//グラフィックアーカイブの読込	(スクリプトの続きからEOFまで)

		//メインイメージ
		m_func._LoadImage ( ifstrm, chara.GetpvpMainTexture() );

		//Efイメージ
		m_func._LoadImage ( ifstrm, chara.GetpvpEfTexture() );

		//---------------------------------------------------------------------
		//ファイルストリーム終了
		ifstrm.close ();


#if 0
		DWORD LoadImage_Time = ::timeGetTime ();
		DWORD t0 = scriptRead_Time - startTime;
		DWORD t1 = Document_Time - scriptRead_Time;
		DWORD t2 = DtoC_Time - Document_Time;
		DWORD t3 = LoadImage_Time - DtoC_Time;
		DBGOUT_WND_F ( 6, _T ( "scriptRead_Time = %d, Document_Time = %d, DtoC_Time = %d, LoadImage_Time = %d" ), t0, t1, t2, t3 );
#endif // 0
	}


}	//namespace GAME

