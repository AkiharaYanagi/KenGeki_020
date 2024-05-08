//=================================================================================================
//
// LoadCharaBin_s3d ソースファイル
//
//=================================================================================================
#include "LoadCharaBin_s3d.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	LoadChara
	//		スクリプトとイメージリストを保存したキャラデータ ".dat"ファイル から、Charaを読み込む
	//==================================================================================
	LoadCharaBin_s3d::LoadCharaBin_s3d ( const s3d::String & filename, Chara & chara )
	{
		try
		{
			_Load ( filename, chara );
		}
		catch ( s3d::Error err )
		{
			TRACE_F_S ( err );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadCharaBin_s3d.\n") );
		}
	}

	//----------------------------------
	//	デストラクタ
	//----------------------------------
	LoadCharaBin_s3d::~LoadCharaBin_s3d ()
	{
	}


	//------------------------------------------
	//	try用実行関数
	//------------------------------------------
	void LoadCharaBin_s3d::_Load ( const s3d::String & filename, Chara & chara )
	{
		//---------------------------------------------------------------------
		//ファイル読込
		s3d::BinaryReader br ( filename );

		//---------------------------------------------------------------------
		//バージョン
		UINT32 version = 0;
		br.read ( version );

		//---------------------------------------------------------------------
		//全体のサイズ
		UINT32 scriptSize = 0;
		br.read ( scriptSize );


		//全体を一時読込
		std::unique_ptr < byte [] > buffer = std::make_unique < byte [] > ( scriptSize );
		br.read ( buffer.get(), scriptSize );

		//------------------------------------------
		//キャラ読込
		UINT pos = 0;	//メモリポインタ

		//スクリプト
		m_func.LoadCharaScript ( std::move ( buffer ), pos, chara );

		//イメージ
		m_func.LoadCharaImage ( std::move ( buffer ), pos, chara );
	}


}	//namespace GAME

