//=================================================================================================
//
//	Training ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Training.h"
#include "../Title/Title.h"
#include "../GameMain/SoundConst.h"
#include "../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
	const float Training::BX = ( 1280 - 206 ) * 0.5f;
	const float Training::BY = 190.f;
	const float Training::BX_KI = ( 1280 - 512 ) * 0.5f;
	const float Training::BY_KI = 900.f;


	Training::Training ()
	{
		//トレーニング表示
		m_training = std::make_shared < GameGraphic > ();
		m_training->AddTexture_FromArchive ( U"training.png" );
		m_training->SetPos ( BX, BY );
		m_training->SetZ ( Z_CH );
		AddpTask ( m_training );
		GRPLST_INSERT ( m_training );

		//戦闘
		m_fighting = std::make_shared < Fighting > ();
		AddpTask ( m_fighting );
		m_fighting->SetActiveTimer ( F );


#if 0
		//キー説明
		m_keyIntro = make_shared < GrpAcv > ();
		m_keyIntro->AddTexture ( _T ( "TRN_keyIntro.png" ) );
		m_keyIntro->SetPos ( BX_KI, BY_KI );
		m_keyIntro->SetZ ( Z_BG - 0.01f );
		AddpTask ( m_keyIntro );
		GRPLST_INSERT_MAIN ( m_keyIntro );

		//ポーズメニュ
		m_pauseMenu = make_shared < Training_Menu > ();
		AddpTask ( m_pauseMenu );

		//ロード中
		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );
		m_rectLoad->Load ();
		m_rectLoad->Move ();
		//開始値、目標値を手動設定
		m_rectLoad->SetFade ( 3, _CLR ( 0xff000000 ), _CLR ( 0x00000000UL ) );
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
#endif // 0
	}

	Training::~Training ()
	{
	}

	void Training::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void Training::Load ()
	{
		//遷移先指定にthisを保存
		Scene::SetwpThis ( shared_from_this () );

		//戦闘共通
		G_Ftg::inst()->Init ();

#if 0
		//Menu用にthisを保存
		m_pauseMenu->SetwpParentScene ( shared_from_this () );

		//CPU / PLAYER
		m_fighting->Set_1P_vs_2P ();
#endif // 0

#if 0

		//SOUND
		SOUND->Stop_BGM ( BGM_GABA );
		SOUND->Play_Loop_BGM ( BGM_GABA );

#endif // 0


		//test
		//DBGOUT_WND()->On ();
		DBGOUT_WND()->Off ();

		Scene::Load ();
	}

	void Training::Init ()
	{
		//デモをスキップ
		m_fighting->SetDemoSkip ();

		Scene::Init ();

		//通常Initの後に行う
		m_fighting->TrainingRestart ();
	}

	void Training::Move ()
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

		//トレーニングリセット
		bool p1Reset = CFG_PUSH_KEY ( P1_BTN6 );
		bool p2Reset = CFG_PUSH_KEY ( P2_BTN6 );
		bool sysReset = WND_UTL::AscKey( '0' );
		if ( p1Reset || p2Reset || sysReset )
		{
			m_fighting->TrainingRestart ();
		}

		//通常動作
		Scene::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//BackSpaceで戻る
		if ( WND_UTL::AscKey ( VK_BACK ) )
		{
//			SOUND->Stop_BGM ( BGM_Main );
			GetwpThis().lock ()->Transit_Title ();
		}

		return Scene::Transit ();
	}



}	//namespace GAME

