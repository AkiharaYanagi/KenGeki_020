//=================================================================================================
//
// LoadChara_s3d ソースファイル
//
//=================================================================================================
#include "LoadChara_s3d.h"
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
	LoadChara_s3d::LoadChara_s3d ( const tstring & filename, Chara & chara ) 
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
			TRACE_F ( _T("Error LoadChara_s3d.\n") );
		}
	}

	//----------------------------------
	//	デストラクタ
	//----------------------------------
	LoadChara_s3d::~LoadChara_s3d ()
	{
	}


	//------------------------------------------
	//	try用実行関数
	//------------------------------------------
	void LoadChara_s3d::_Load ( const tstring & filename, Chara & chara )
	{
		//---------------------------------------------------------------------
		//初期化
		chara.Clear ();

		//---------------------------------------------------------------------
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

		//Documentを生成
		Document document ( scriptBuf, scriptSize );

		//一時読込の破棄
		delete[] scriptBuf;

		//キャラデータに変換
		m_func._DocumentToChara ( document, chara );


		//---------------------------------------------------------------------
		//グラフィックアーカイブの読込	(スクリプトの続きからEOFまで)

		//メインイメージ
		m_func._LoadImage ( ifstrm, chara.GetpvpMainTexture() );

		//Efイメージ
		m_func._LoadImage ( ifstrm, chara.GetpvpEfTexture() );

		//---------------------------------------------------------------------
		//ファイルストリーム終了
		ifstrm.close ();

	}


}	//namespace GAME

