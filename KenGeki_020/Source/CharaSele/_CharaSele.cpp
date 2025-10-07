//=================================================================================================
//
//	_CharaSele ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_CharaSele.h"
#include "../GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	_CharaSele::_CharaSele ()
	{
		//BG(全体)
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"CharaSele\\CharaSele_BG.png" );
		m_bg->SetPos ( 0, 0 );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		//Scroll(全体)
		m_scroll = std::make_shared < GameGraphic > ();
		m_scroll->SetShader ( T );
		m_scroll->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll.png" );
		m_scroll->SetPos ( 0, 0 );
		m_scroll->SetZ ( Z_BG );
		AddpTask ( m_scroll );
		GRPLST_INSERT ( m_scroll );

		//CharaFace
		m_charaFace = std::make_shared < GameGraphic > ();
		m_charaFace->AddTexture_FromArchive ( U"CharaSele\\CharaFace.png" );
		m_charaFace->SetPos ( (1280 - 455) / 2, 70 );
		m_charaFace->SetZ ( Z_EFF );
		AddpTask ( m_charaFace );
		GRPLST_INSERT ( m_charaFace );

		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		m_fade_toTitle->SetAfterClear ( F );
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		m_fade_toFighting->SetAfterClear ( F );
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );


		//-----------------------------------------------------------------------

		//共有テクスチャ
		m_img_cmn = std::make_shared < CharaSele_Image_Common > ();

		//キャラセレ　プレイヤ別処理
		m_player_1p = std::make_shared < _CharaSele_Player > ();
		m_player_1p->PlayerInit ( PLAYER_ID_1 );
		m_player_1p->LoadTx ( m_img_cmn );
		AddpTask ( m_player_1p );

		m_player_2p = std::make_shared < _CharaSele_Player > ();
		m_player_2p->PlayerInit ( PLAYER_ID_2 );
		m_player_2p->LoadTx ( m_img_cmn );
		AddpTask ( m_player_2p );

		//-----------------------------------------------------------------------
		//1P2P表示
		m_index_1p = std::make_shared < GameGraphic > ();
		m_index_1p->AddTexture_FromArchive ( U"CharaSele\\1P_Index.png" );
		m_index_1p->SetPos ( CH_INDEX_X_1P, CH_INDEX_Y );
		AddpTask ( m_index_1p );
		GRPLST_INSERT ( m_index_1p );

		m_index_2p = std::make_shared < GameGraphic > ();
		m_index_2p->AddTexture_FromArchive ( U"CharaSele\\2P_Index.png" );
		m_index_2p->SetPos ( CH_INDEX_X_2P, CH_INDEX_Y );
		AddpTask ( m_index_2p );
		GRPLST_INSERT ( m_index_2p );

		//文字表示
		const s3d::String fn_crsl = U"CharaSele\\Text_CHARACTER_SELECT.png";
		m_txt_CharacterSelect = MakeTxtGrp ( VEC2 ( TXT_CHSL_X, TXT_CHSL_Y ), fn_crsl );

		//-----------------------------------------------------------------------
		//ステージ
		m_stage = std::make_shared < CharaSele_Stage > ();
		AddpTask ( m_stage );

		//BGM
		m_bgm = std::make_shared < CharaSele_BGM > ();
		AddpTask ( m_bgm );

		//-----------------------------------------------------------------------
		//1P2P表示
		m_OK = std::make_shared < GameGraphic > ();
		m_OK->AddTexture_FromArchive ( U"CharaSele\\OK.png" );
		m_OK->AddObject ();
		m_OK->GetpObject ( 0 )->SetPos ( OK_X_1P, OK_Y );
		m_OK->GetpObject ( 1 )->SetPos ( OK_X_2P, OK_Y );
		m_OK->GetpObject ( 0 )->SetValid ( F );
		m_OK->GetpObject ( 1 )->SetValid ( F );
		AddpTask ( m_OK );
		GRPLST_INSERT ( m_OK );

		//-----------------------------------------------------------------------
		//操作説明
		m_inst = std::make_shared < GameGraphic > ();
		m_inst->AddTexture_FromArchive ( U"CharaSele\\Inst_CharaSele.png" );
		m_inst->SetPos ( VEC2 ( INST_X, INST_Y ) );
		m_inst->SetZ ( Z_SYS );
		AddpTask ( m_inst );
		GRPLST_INSERT ( m_inst );

	}


	_CharaSele::~_CharaSele ()
	{
	}


	void _CharaSele::ParamInit ()
	{
		P_Param p = GetpParam ();
		m_player_1p->ParamInit ( p );
		m_player_2p->ParamInit ( p );

		m_stage->SetStage ( p->GetStage_Name () );
	}

	void _CharaSele::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		//thisの設置
		m_player_1p->SetwpCharaSele ( shared_from_this () );
		m_player_2p->SetwpCharaSele ( shared_from_this () );

		//互いの設置
		m_player_1p->SetwpOther ( m_player_2p );
		m_player_2p->SetwpOther ( m_player_1p );

		//SOUND
		SND_STOP_ALL_BGM();
		SND_PLAY_LOOP_BGM ( BGM_CharaSele );	//初期BGMはキャラセレBGM

		Scene::Load ();
	}

	void _CharaSele::Move ()
	{
		//----------------------------------------------------------
		//背景スクロール
		//	@proc 常に実行
		m_scrl_y -= 20;
		if ( m_scrl_y < - 960 ) { m_scrl_y = 0; }
		m_scroll->SetPos ( 0, m_scrl_y );

		//----------------------------------------------------------
		//フェードアウト中の待機と遷移
		//	@proc シーン移行時

		//タイトルに移行中
		if ( m_fade_toTitle->IsActive() )
		{
			Scene::Move (); 
			return;
		}

		//戦闘に移行中
		if ( m_fade_toFighting->IsActive () )
		{
			Scene::Move (); 
			return;
		}


		//----------------------------------------------------------
		//入力
		//	@proc シーン移行以外
		Input ();


		//----------------------------------------------------------
		//両者すべてを決定したらFtgMainに移行
		if ( ! m_fade_toFighting->IsActive () )
		{
			bool bOK1 = m_player_1p->Is_OK ();
			bool bOK2 = m_player_2p->Is_OK ();
			if ( bOK1 && bOK2 )
			{
				//フェード開始
				m_fade_toFighting->StartBlackOut ( 16 );
			}
		}

		//----------------------------------------------------------
		Scene::Move (); 
	}



	P_GameScene _CharaSele::Transit ()
	{
		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM();
			Scene::Transit_Title ();
		}

		//戦闘に移行
		if ( m_fade_toFighting->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM ();

			m_fade_toFighting->ShiftTargetColor ();

			//通常戦闘かトレーニングの分岐
			P_Param pPrm = Scene::GetpParam ();
			if ( MODE_FTG_MAIN == pPrm->GetGameMode () )
			{
				Scene::Transit_Fighting ();
			}
			else if ( MODE_TRAINING == pPrm->GetGameMode () )
			{
				Scene::Transit_Training ();
			}
		}

		//通常時は自身を返す
//		return shared_from_this ();
		//他のシーンが確保されたなら遷移する
		return Scene::Transit (); 
	}




	CHARA_NAME _CharaSele::GetOtherChara ( PLAYER_ID id )
	{
		CHARA_NAME name = CHARA_OUKA;
		if ( PLAYER_ID_1 == id )
		{
			name = m_player_2p->GetCharaName ();
		}
		else if ( PLAYER_ID_2 == id )
		{
			name = m_player_1p->GetCharaName ();
		}
		return name;
	}

	CHARA_COLOR _CharaSele::GetOtherColor ( PLAYER_ID id )
	{
		CHARA_COLOR color = CH_CLR_2;
		if ( PLAYER_ID_1 == id )
		{
			color = m_player_2p->GetColor ();
		}
		else if ( PLAYER_ID_2 == id )
		{
			color = m_player_1p->GetColor ();
		}
		return color;
	}


	//=========================================
	//	内部関数
	//=========================================

	//キャラ選択、ステージ選択をパラメータに記録
	void _CharaSele::Save ()
	{
		//パラメータに記録し、次シーン以降で用いる
		P_Param pPrm = Scene::GetpParam ();
		pPrm->SetCharaName1p ( m_player_1p->GetCharaName() );
		pPrm->SetCharaName2p ( m_player_2p->GetCharaName() );
		pPrm->SetCharaColor1p ( m_player_1p->GetColor() );
		pPrm->SetCharaColor2p ( m_player_2p->GetColor() );
		pPrm->SetStage_Name ( m_stage->GetStageName () );
		pPrm->Set_BGM_ID ( m_bgm->Get_ID () );


		//設定ファイルに書出
		pPrm->GetGameSetting().Save ();
	}



	void _CharaSele::Input ()
	{
		//BackSpaceでタイトルに戻る (ESCは直接終了)
		//コントローラ(7:リセットボタン)でも戻る
		if ( ! m_fade_toTitle->IsActive () )
		{
			bool bBackSpace = WND_UTL::AscKey ( VK_BACK );
			bool bCtrlReset = CFG_PUSH_KEY_12 ( PLAYER_INPUT::PLY_BTN7 );
			if ( bBackSpace || bCtrlReset )
			{
				SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

				//フェード開始
				m_fade_toTitle->StartBlackOut ( 8 );
			}
		}

		m_player_1p->Input ();
		m_player_2p->Input ();
	}



	void _CharaSele::OK_On_1p ()
	{
		m_OK->GetpObject ( 0 )->SetValid ( T );
	}

	void _CharaSele::OK_Off_1p ()
	{
		m_OK->GetpObject ( 0 )->SetValid ( F );
	}

	void _CharaSele::OK_On_2p ()
	{
		m_OK->GetpObject ( 1 )->SetValid ( T );
	}

	void _CharaSele::OK_Off_2p ()
	{
		m_OK->GetpObject ( 1 )->SetValid ( F );
	}



	//文字表示グラフィックの作成
	P_GrpBlink _CharaSele::MakeTxtGrp ( VEC2 pos, const s3d::String & filename )
	{
		P_GrpBlink pGrp = std::make_shared < GrpBlink > ();
		pGrp->AddTexture_FromArchive ( filename );
		pGrp->SetPos ( pos );
		pGrp->SetZ ( Z_SYS );
		pGrp->Stop ();
		pGrp->SetHalf ( T );
		GRPLST_INSERT ( pGrp );
		return pGrp;
	}


#pragma region CONST

	//キャラセレ
	const float _CharaSele::TXT_CHSL_X = 640 - 270 / 2;
	const float _CharaSele::TXT_CHSL_Y = 24;

	//キャラ別
	const float _CharaSele::CH_INDEX_X_1P = 100;
	const float _CharaSele::CH_INDEX_X_2P = 1280 - 194 - CH_INDEX_X_1P;
	const float _CharaSele::CH_INDEX_Y = 5;

	const float _CharaSele::CH_BAR_X_1P = 405;
	const float _CharaSele::CH_BAR_X_2P = 405;
	const float _CharaSele::CH_BAR_Y = 0;

	//操作説明
	const float _CharaSele::INST_X = 0;
	const float _CharaSele::INST_Y = 960 - 27;

	//OK
	const float _CharaSele::OK_X_1P = - 50;
	const float _CharaSele::OK_X_2P = 1280 - 500 - OK_X_1P;
	const float _CharaSele::OK_Y = - 10;

#pragma endregion



}	//namespace GAME

