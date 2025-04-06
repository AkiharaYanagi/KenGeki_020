//=================================================================================================
//
//	CharaSele_Stage
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Stage.h"
#include "../GameMain/SeConst.h"
#include "../GameMain/SoundConst.h"
#include "_CharaSele.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	CharaSele_Stage::CharaSele_Stage ()
	{
		//プレビュー画像
		m_stageSelect = std::make_shared < GameGraphic > ();
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Susuki_Noon.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Susuki_Evening.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Susuki_Night.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_School_Morning.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_School_Noon.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_School_Night.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Taishou_Morning.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Taishou_Noon.png" );
		m_stageSelect->AddTexture_FromArchive ( U"CharaSele\\BG_Preview_Taishou_Night.png" );
		m_stageSelect->SetPos ( VEC2 ( STG_X, STG_Y ) );
		m_stageSelect->SetZ ( Z_EFF );
		AddpTask ( m_stageSelect );
		GRPLST_INSERT ( m_stageSelect );

		//選択矢印
		m_stageSelectTri = std::make_shared < GrpBlink > ();
		m_stageSelectTri->AddTexture_FromArchive ( U"CharaSele\\SelectTriangleStage.png" );
		m_stageSelectTri->SetPos ( VEC2 ( STG_TRI_X, STG_TRI_Y ) );
		m_stageSelectTri->SetZ ( Z_EFF );
		m_stageSelectTri->SetHalf ( T );
		AddpTask ( m_stageSelectTri );
		GRPLST_INSERT ( m_stageSelectTri );

		//文字表示
		const s3d::String filename = U"CharaSele\\Text_STAGE_SELECT.png";
		VEC2 pos { TXT_STSL_X, TXT_STSL_Y };
		m_txt_StageSelect = _CharaSele::MakeTxtGrp ( pos, filename );
		AddpTask ( m_txt_StageSelect );

		//Scroll Stage
		m_scroll_Stage = std::make_shared < GameGraphic > ();
		m_scroll_Stage->SetShader ( T );
		m_scroll_Stage->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Scroll_Stage.png" );
		m_scroll_Stage->SetPos ( STG_BG_X, STG_BG_Y );
		m_scroll_Stage->SetZ ( Z_BG );
		AddpTask ( m_scroll_Stage );
		GRPLST_INSERT ( m_scroll_Stage );

	}

	CharaSele_Stage::~CharaSele_Stage ()
	{
	}

	//-------------------------------------------------
	void CharaSele_Stage::Move ()
	{
		m_scrlStg_x -= 20;
		if ( m_scrlStg_x < - 1280 ) { m_scrlStg_x = 0; }
		m_scroll_Stage->SetPos ( m_scrlStg_x, STG_BG_Y );

		TASK_VEC::Move ();
	}

	//-------------------------------------------------
	void CharaSele_Stage::On ()
	{
		m_stageSelectTri->Start ();
		m_txt_StageSelect->Start ();
	}
	void CharaSele_Stage::Off ()
	{
		m_stageSelectTri->Stop ();
		m_txt_StageSelect->Stop ();
	}


	void CharaSele_Stage::Prev ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_stageSelect->PrevIndexTexture ();
	}

	void CharaSele_Stage::Next ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_move );
		m_stageSelect->NextIndexTexture ();
	}

	void CharaSele_Stage::Decide ()
	{
		SND_PLAY_ONESHOT_SE ( SE_select_decide );
//		m_stageDecide = T;

		//BGM選択に以降するときに初期値で変更する
		SND_STOP_ALL_BGM();
//		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ m_bgm_id ] );

	}


	void CharaSele_Stage::SetStage ( STAGE_NAME name )
	{
		m_stageSelect->SetIndexTexture ( (uint32)name );
	}


	//ステージセレクト
	const float CharaSele_Stage::STG_BG_X = 0;
	const float CharaSele_Stage::STG_BG_Y = 385;
	const float CharaSele_Stage::STG_X = 640 - 256 / 2;
	const float CharaSele_Stage::STG_Y = 420;
	const float CharaSele_Stage::STG_TRI_X = (1280 - 335) * 0.5f;
	const float CharaSele_Stage::STG_TRI_Y = STG_Y + 50;
	const float CharaSele_Stage::TXT_STSL_X = 640 - 260 / 2;
	const float CharaSele_Stage::TXT_STSL_Y = 390;


}	//namespace GAME

