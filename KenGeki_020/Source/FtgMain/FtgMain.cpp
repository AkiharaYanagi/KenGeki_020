//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../Title/Title.h"
#include "../GameMain/G_Ftg.h"
#include "../GameMain/SoundConst.h"

#if 0
#include "../Result/Result.h"
#endif // 0



//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
		//戦闘
		m_fighting = std::make_shared < Fighting > ();
		AddpTask ( m_fighting );

#if 0
		//ポーズメニュ
		m_pauseMenu = make_shared < PauseMenu > ();
		AddpTask ( m_pauseMenu );

		//ロード中
		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );

		m_rectLoad->Load ();
		m_rectLoad->Move ();

//		m_rectLoad->SetFadeOut ( 10 );	//SetFadeOut()は0xffffffff->0x00ffffffなので白くなる
		m_rectLoad->SetFade ( 3, _CLR(0xff000000), _CLR(0x00000000UL) );	//開始値、目標値を手動設定

		AddpTask ( m_rectLoad );
		GRPLST_INSERT_MAIN ( m_rectLoad );
		m_wait = 0;

		
		m_NowLoading = make_shared < GrpStr > ();
		m_NowLoading->SetStr ( _T ( "Now Loading..." ) );
		m_NowLoading->SetPos ( VEC2 ( 1000, 915 ) );
		m_NowLoading->Load ();
		m_NowLoading->Move ();
		m_NowLoading->SetZ ( Z_FADE - 0.01f );
		AddpTask ( m_NowLoading );
		GRPLST_INSERT_MAIN ( m_NowLoading );


		//----------------------------------------------------
		//@info コンストラクタでshared_from_this()を用いない
#endif // 0
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::Load ()
	{
		//戦闘共通
		G_Ftg::inst()->Init ();

		//遷移先指定にthisを保存
		Scene::SetwpThis ( shared_from_this () );
#if 0
		//Menu用にthisを保存
		m_pauseMenu->SetwpParentScene ( shared_from_this () );
#endif // 0


		//test
//		DBGOUT_WND()->On ();
		DBGOUT_WND()->Off ();


		Scene::Load ();
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( Scene::GetpParam () );

		//BGM
//		SOUND->Play_Loop_BGM ( BGM_Main );
	}


	void FtgMain::Move ()
	{
#if 0
		//NowLoading終了
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}

		//メニュポーズ中
		if ( m_pauseMenu->MenuCheck () )
		{
			return;
		}
#endif // 0

		//デモ リスタート
		if ( WND_UTL::AscKey ( '0' ) )
		{
			m_fighting->DemoRestart ();
		}

		//トレーニングリセット
		bool p1Reset = CFG_PUSH_KEY ( P1_BTN6 );
		bool p2Reset = CFG_PUSH_KEY ( P2_BTN6 );
		bool sysReset = WND_UTL::AscKey ( VK_BACK );
		if ( p1Reset || p2Reset || sysReset )
		{
			m_fighting->TrainingRestart ();
		}

		//通常動作
		Scene::Move ();

#if 0
		//終了チェック
		if ( m_fighting->IsEnd () )
		{
#if 0
			//BGM
			SOUND->Stop_BGM ( BGM_Main );
			Scene::Transit_Result ();

#endif // 0
		}
#endif // 0
	}

	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		return Scene::Transit ();
	}
	
}	//namespace GAME

