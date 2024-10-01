//=================================================================================================
//
//	CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgMain/FtgConst.h"	
#include "../GameMain/Scene.h"
#include "CharaSeleConst.h"
#include "CharaSele_Player.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaSele : public Scene, public std::enable_shared_from_this < CharaSele >
	{
		//BG
		P_Grp			m_bg;

		//Scroll
		P_Grp			m_scroll;
		float			m_scrl_y { 0 };
		P_Grp			m_scroll_Stage;
		float			m_scrlStg_x { 0 };

		//CharaFace
		P_Grp			m_charaFace;

		//カーソル
		P_GrpBlink		m_cursor1p;
		P_GrpBlink		m_cursor2p;

		//選択ID
		CHARA_SELE_ID	m_chslct_id_1p { CHSLID_00 };	//現在位置1p
		CHARA_SELE_ID	m_chslct_id_2p { CHSLID_02 };	//現在位置2p

		//プレイヤー毎位置
		P_ChSele_Pl		m_chsl_pl_1p;
		P_ChSele_Pl		m_chsl_pl_2p;

		//フェード
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
//		bool			m_endWait { F };
		uint32			m_plus_wait { 0 };

		//モード保存
		MUTCH_MODE		m_mode { MODE_PLAYER_PLAYER };


		//ステージセレクト
		P_Grp			m_stageSelect;
		bool			m_stageDecide { F };

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit ();
		void Load ();
		void Move ();

		P_GameScene Transit ();

	private:
		void Input ();
		STAGE_NAME GetStageName ();

	};


}	//namespace GAME


