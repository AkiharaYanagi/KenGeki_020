//=================================================================================================
//
// LoadCharaBin_s3d ソースファイル
//
//=================================================================================================
#include "LoadCharaBin_s3d.h"
#include <filesystem>
#include "LoadImgFile.h"

using namespace std::chrono;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using CLK = std::chrono::steady_clock;


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
	//filename : "chara_***.dat"
	void LoadCharaBin_s3d::_Load ( const s3d::String & filename, Chara & chara )
	{
		std::filesystem::path current_path = std::filesystem::current_path();

		//ファイル存在確認
		if ( ! std::filesystem::exists  ( filename.str() ) ) { return; }

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
		if ( scriptSize > 1000000000u ) { assert (0); };	//1[GB]以上はアサート

		//全体を一時読込
		UP_BYTE buffer = std::make_unique < byte [] > ( scriptSize );
		br.read ( buffer.get(), scriptSize );

		//------------------------------------------
		//キャラ読込
		UINT pos = 0;	//メモリポインタ

		//スクリプト
		m_func.LoadCharaScript ( std::move ( buffer ), pos, chara );

		//イメージ
		m_func.LoadCharaImage ( std::move ( buffer ), pos, chara );

#if 0
		LoadImgFile lif;
		s3d::String fn = filename.substr ( 0, filename.length() - 4 );
		s3d::String filename_bhv = fn + U"_bhv.atls";
		s3d::String filename_gns = fn + U"_gns.atls";
		chara.SetpapTx_Main ( lif.LoadAtlas ( filename_bhv ) );
		chara.SetpapTx_Ef ( lif.LoadAtlas ( filename_gns ) );
#endif // 0

#if 0

		//時間計測
		CLK::time_point start_time = CLK::now ();


		//読込
		LoadImgFile loadImgFile;

		size_t len = filename.length();
		s3d::String fn = filename.substr ( 0, len - 4 );

		s3d::String filename_bhv = fn + U"_bhv.img";
		chara.SetpapTx_Main ( loadImgFile.Do ( filename_bhv ) );

		s3d::String filename_gns = fn + U"_gns.img";
		chara.SetpapTx_Ef ( loadImgFile.Do ( filename_gns ) );


		//時間計測
		CLK::time_point end_time = CLK::now ();
		duration drtn = duration_cast < microseconds > ( end_time - start_time );
		long long ms = drtn.count ();
		s3d::Logger << ms;


		loadImgFile.Conversion ( filename_bhv );
#endif // 0
	}


}	//namespace GAME

