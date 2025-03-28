﻿//=================================================================================================
//
//	BG ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "BG.h"
#include "../FtgConst.h"	
#include "../../GameMain/G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//	const float BG::BG_SIZE_W = 2048;
	const float BG::BG_SIZE_W = 1920;
//	const float BG::BG_SIZE_H = 1024;
	const float BG::BG_SIZE_H = 960;
	const float BG::BG_POS_X = 0 - ( BG_SIZE_W - 1280 ) / 2;
//	const float BG::BG_POS_Y = 0 - ( 1024 - 960 );
//	const float BG::BG_POS_Y = 0 - ( 1080 - 960 );
	const float BG::BG_POS_Y = 0 - ( 960 - BG_SIZE_H );

	BG::BG ()
	{
		//------------------------------------------------
		//背景 中
		m_bg_C = std::make_shared < GameGraphic > ();
		m_bg_C->SetPos ( 0, BG_POS_Y );
		m_bg_C->SetZ ( Z_BG );
		AddpTask ( m_bg_C );
		GRPLST_INSERT ( m_bg_C );

		//------------------------------------------------
		//背景 左
		m_bg_L = std::make_shared < GameGraphic > ();
		m_bg_L->SetPos ( -BG_SIZE_W, BG_POS_Y );
		m_bg_L->SetZ ( Z_BG );
		AddpTask ( m_bg_L );
		GRPLST_INSERT ( m_bg_L );

		//------------------------------------------------
		//背景 右
		m_bg_R = std::make_shared < GameGraphic > ();
		m_bg_R->SetPos ( BG_SIZE_W, BG_POS_Y );
		m_bg_R->SetZ ( Z_BG );
		AddpTask ( m_bg_R );
		GRPLST_INSERT ( m_bg_R );

		//------------------------------------------------



		//------------------------------------------------
		//test 壁位置
		m_wall_L = std::make_shared < GameGraphic > ();
		m_wall_L->AddTexture_FromArchive ( U"test_kabe.png" );
		m_wall_L->SetPos ( 0, 0 );
		m_wall_L->SetZ ( Z_BG );
		AddpTask ( m_wall_L );
		//		GRPLST_INSERT ( m_wall_L );

		m_wall_R = std::make_shared < GameGraphic > ();
		m_wall_R->AddTexture_FromArchive ( U"test_kabe.png" );
		m_wall_R->SetScaling ( -1.f, 1.f );
		m_wall_R->SetPos ( GAME_WIDTH - 512, 0 );
		m_wall_R->SetZ ( Z_BG );
		AddpTask ( m_wall_R );
		//		GRPLST_INSERT ( m_wall_R );


		//------------------------------------------------
		//test 入力説明
		m_input = std::make_shared < GameGraphic > ();
		m_input->AddTexture_FromArchive ( U"Input.png" );
		m_input->SetPos ( 320, 300 );
		m_input->SetZ ( Z_BG );
		AddpTask ( m_input );
		GRPLST_INSERT ( m_input );

		m_input->SetValid ( F );


		LoadFrontOb ();


#if 0

//テスト
		m_bg_back = make_shared < GrpAcv > ();
		m_bg_back->AddTexture ( _T ( "BG0_Back.png" ) );
		m_bg_back->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_back->SetZ ( Z_BG );

		m_bg_middle = make_shared < GrpAcv > ();
		m_bg_middle->AddTexture ( _T ( "BG0_Middle.png" ) );
		m_bg_middle->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_middle->SetZ ( Z_BG );

		m_bg_front = make_shared < GrpAcv > ();
		m_bg_front->AddTexture ( _T ( "BG0_Front.png" ) );
		m_bg_front->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_front->SetZ ( Z_BG );

		AddpTask ( m_bg_back );
		GRPLST_INSERT_MAIN ( m_bg_back );
		AddpTask ( m_bg_middle );
		GRPLST_INSERT_MAIN ( m_bg_middle );
		AddpTask ( m_bg_front );
		GRPLST_INSERT_MAIN ( m_bg_front );
#endif // 0

#if 0
		//------------------------------------------------
		//BGタイマ
		//暗転
		m_tmrBlackOut = std::make_shared < Timer > ();
		AddpTask ( m_tmrBlackOut );

		//------------------------------------------------
		//白背景
		m_bg_white = make_shared < PrmRect > ();
		m_bg_white->SetSize ( 1280, 960 );
		m_bg_white->SetAllColor ( 0xffffffff );
		m_bg_white->SetPos ( 0, 0 );
		m_bg_white->SetZ ( Z_BG );
		AddpTask ( m_bg_white );
		GRPLST_INSERT_MAIN ( m_bg_white );
		m_bg_white->SetValid ( F );


		//白転
		m_tmrWhiteOut = make_shared < Timer > ();
		AddpTask ( m_tmrWhiteOut );

		//------------------------------------------------

		//壁割り
		m_wall_break = make_shared < GrpAcv > ();
		m_wall_break->AddTexture ( _T("glass.png") );
		m_wall_break->AddTexture ( _T("break0.png") );
		m_wall_break->AddTexture ( _T("break1.png") );
		m_wall_break->AddTexture ( _T("break2.png") );
		m_wall_break->AddTexture ( _T("break3.png") );
		m_wall_break->SetScaling ( 0.5f, 1.f );
		AddpTask ( m_wall_break );
		GRPLST_INSERT_MAIN ( m_wall_break );
		m_wall_break->SetValid ( F );

		m_tmrWallBreak = make_shared < Timer > ();
		AddpTask ( m_tmrWallBreak );
#endif // 0
	}

	BG::~BG ()
	{
	}

	void BG::Load ()
	{
		TASK_VEC::Load ();
	}



	void BG::ParamInit ( P_Param pParam )
	{
		m_stage_name = pParam->GetStage_Name ();

		switch ( m_stage_name )
		{
		case STAGE_ASAHINO_HARA:
			m_bg_C->AddTexture_FromArchive ( U"BG\\BG_noon_C.png" );
			m_bg_L->AddTexture_FromArchive ( U"16_16_Padding.png" );
			m_bg_R->AddTexture_FromArchive ( U"16_16_Padding.png" );
		break;

		case STAGE_YUUHINO_HARA:
			m_bg_C->AddTexture_FromArchive ( U"BG\\BG_evening_C.png" );
			m_bg_L->AddTexture_FromArchive ( U"16_16_Padding.png" );
			m_bg_R->AddTexture_FromArchive ( U"16_16_Padding.png" );
		break;

		case STAGE_YORUNO_HARA :
			m_bg_C->AddTexture_FromArchive ( U"BG\\BG_night_C.png" );
			m_bg_L->AddTexture_FromArchive ( U"16_16_Padding.png" );
			m_bg_R->AddTexture_FromArchive ( U"16_16_Padding.png" );
		break;

		case STAGE_SCHOOL_NOON:
			m_bg_C->AddTexture_FromArchive ( U"BG\\BG_Taishou_morning.png" );
			m_bg_L->AddTexture_FromArchive ( U"16_16_Padding.png" );
			m_bg_R->AddTexture_FromArchive ( U"16_16_Padding.png" );
		break;

		}
	}


	void BG::Init ()
	{
#if 0
		m_bg_black->SetValid ( F );
		m_bg_white->SetValid ( F );

		m_tmrBlackOut->Clear ();
		m_tmrWhiteOut->Clear ();
		m_tmrWallBreak->Clear ();

#endif // 0
		TASK_VEC::Init ();
	}


	void BG::Move ()
	{
#if 0
		m_front->SetDispBase ( G_BASE_POS () );
		m_front->NextIndexTexture ();
#endif // 0


#if 0
		//--------------------------
		//暗転
		if ( m_tmrBlackOut->IsActive () )	//稼働時
		{
			//終了
			if ( m_tmrBlackOut->IsLast () )
			{
				m_tmrBlackOut->Clear ();
				m_bg_black->SetValid ( F );
			}
		}

		//白転
		if ( m_tmrWhiteOut->IsActive () )	//稼働時
		{
			//終了
			if ( m_tmrWhiteOut->IsLast () )
			{
				m_tmrWhiteOut->Clear ();

				m_bg_white->SetValid ( F );
			}
		}

		//壁割り
		if ( m_tmrWallBreak->IsActive () )
		{
			//終了
			if ( m_tmrWallBreak->IsLast () )
			{
				m_wall_break->SetIndexTexture ( m_indexTexture );
				if ( ++ m_indexTexture > 3 )
				{
					m_indexTexture = 0; 
					m_wall_break->SetValid ( F );
				} 
				m_tmrWallBreak->Start ( 6 );
			}
		}

#endif // 0
		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
		TASK_VEC::Move ();
	}

	//=============================================================
	//	内部関数
	//=============================================================



	//共通グラフィック処理
	void BG::Grp ()
	{
		//-------------------------------------------------------
		//背景位置補正
		int nx = (int) G_BASE_POS ().x;
//		int disp_bg_x = nx % GAME_WIDTH;
		int disp_bg_x = nx;
		int POINT = (1280 - 2048) / 2;	//切り替えポイント


//		DBGOUT_WND_F( U"G_BASE_POS = {}"_fmt( disp_bg_x ) );

		//Left
		if ( disp_bg_x < POINT )
		{
			m_bg_L->SetPos ( (float)(disp_bg_x + 4096), BG_POS_Y );
		}
		else
		{
			m_bg_L->SetPos ( (float)(disp_bg_x - 2048), BG_POS_Y );
		}

		//Center
		if ( disp_bg_x < POINT - 2048 )
		{
			m_bg_C->SetPos ( (float)(disp_bg_x + 4096 + 2048), BG_POS_Y );
		}
		else
		{
			m_bg_C->SetPos ( (float)disp_bg_x, BG_POS_Y );
		}

		//Right
		if ( disp_bg_x < POINT - 4096 )
		{
			m_bg_R->SetPos ( (float)(disp_bg_x + 4096 + 4096 ), BG_POS_Y );
		}
		else
		{
			m_bg_R->SetPos ( (float)(disp_bg_x + 2048), BG_POS_Y );
		}


#if 0
		//サブ背景位置
		int lx = disp_bg_x - GAME_WIDTH;
		int rx = disp_bg_x + GAME_WIDTH;
		const int D = GAME_WINDOW_WIDTH - GAME_WIDTH;	//2048 - 1280 = 768
		int sub_x = ( - disp_bg_x < 0 )? lx : rx ;
		P_Object pOb = m_bg->GetpObject ( 1 );
		pOb->SetPos ( (float)sub_x, (float)BG_POS_Y );


#endif // 0
		//-------------------------------------------------------
		//カベ位置
		float wall_l = G_FTG()->GetWallLeft ();
		m_wall_L->SetPos ( wall_l + G_BASE_POS ().x, 0 );
//		m_wall_L->SetPos ( 4096 + G_BASE_POS ().x, 0 );

		float wall_r = G_FTG()->GetWallRight ();
		m_wall_R->SetPos ( wall_r + G_BASE_POS ().x, 0 );
//		m_wall_R->SetPos ( -2048 + G_BASE_POS ().x, 0 );


#if 0
		//-------------------------------------------------------
		//暗転
		if ( ! m_tmrBlackOut->IsActive () )
		{
			UINT blackOut = m_mutualChara->GetBlackOut ();

			//初回
			if ( 0 < blackOut )
			{
				m_tmrBlackOut->Start ( blackOut );

				blackOut = 0;
				m_mutualChara->SetBlackOut ( 0 );

//				m_bg->SetValid ( F );
//				m_bg_blackout->SetValid ( T );
			}
		}

		//-------------------------------------------------------
		//白転
		if ( ! m_tmrWhiteOut->IsActive () )
		{
			//初回
			if ( m_mutualChara->CheckWhiteOut () )
			{
				m_tmrWhiteOut->Start ( 30 );

				m_bg_white->SetValid ( T );
				m_mutualChara->SetWhiteOut ( F );
			}
		}

#endif // 0



//		static bool bDisp = T;		//状態
		static bool bDisp = F;		//状態
		static bool pre_Input = F;	//前回押しているか
		static bool is_Input = F;	//今回押しているか

		is_Input = ( WND_UTL::AscKey ( '1' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_Input && is_Input )	// false -> true
		{
			if ( bDisp )
			{
				m_input->SetValid ( F );
				bDisp = false;
			}
			else
			{
				m_input->SetValid ( T );
				bDisp = true;
			}
		}

		pre_Input = is_Input;

	}


#if 0

	void BG::SetBlackOut ( bool b )
	{
		m_bg_black->SetValid ( b );
	}

	void BG::OnBlackOut ()
	{
		m_bg_black->SetValid ( T );
	}

	void BG::OffBlackOut ()
	{
		m_bg_black->SetValid ( F );
	}

	void BG::SetWhiteOut ( UINT n )
	{
		m_tmrWhiteOut->Start ( n );
		m_bg_white->SetValid ( T );
	}

	void BG::StartWallBreak_L ()
	{
		m_tmrWallBreak->Start ( 4 );
		m_wall_break->SetPos ( 0, 0 );
		m_wall_break->SetValid ( T );
	}
	void BG::StartWallBreak_R ()
	{
		m_tmrWallBreak->Start ( 4 );
		m_wall_break->SetValid ( T );
		m_wall_break->SetPos ( GAME_WINDOW_WIDTH / 2, 0 );
	}


#endif // 0


	void BG::LoadFrontOb ()
	{
#if 0

		//------------------------------------------------
		m_front = std::make_shared < GrpEf > ();
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_00.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_01.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_02.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_03.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_04.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_05.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_06.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_07.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_08.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_09.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_10.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_11.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_12.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_13.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_14.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_15.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_16.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_17.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_18.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_19.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_20.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_21.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_22.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_23.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_24.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_25.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_26.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_27.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_28.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_29.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_30.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_31.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_32.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_33.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_34.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_35.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_36.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_37.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_38.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_39.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_40.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_41.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_42.png" );
		m_front->AddTexture_FromArchive ( U"front_loop\\Front_Ob_43.png" );
		m_front->SetBase ( VEC2 ( 600, 600 ) );
		m_front->SetZ ( Z_SYS );
		m_front->On ();
		AddpTask ( m_front );
		GRPLST_INSERT ( m_front );

#endif // 0
	}


}	//namespace GAME

