//=================================================================================================
//
//	_CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "CharaSele_Image.h"
#include "_CharaSele_Player.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele : public Scene, public std::enable_shared_from_this < _CharaSele >
	{
		//BG
		P_Grp			m_bg;

		//CharaFace
		P_Grp			m_charaFace;

		//CharaTx
		P_ChSl_Img_Cmn	m_img_cmn;

		//キャラセレ　プレイヤ別処理
		P_ChSl_Pl		m_player_1p;
		P_ChSl_Pl		m_player_2p;

		//1P2P表示
		P_Grp			m_index_1p;
		P_Grp			m_index_2p;

		//文字表示
		P_GrpBlink		m_txt_CharacterSelect;

	public:
		_CharaSele ();
		_CharaSele ( const _CharaSele & rhs ) = delete;
		~_CharaSele ();

		void ParamInit ();
		void Load ();
		P_GameScene Transit ();


#pragma region CONST

		//位置
		static const float TXT_CHSL_X;
		static const float TXT_CHSL_Y;

		static const float CH_INDEX_X_1P;
		static const float CH_INDEX_X_2P;
		static const float CH_INDEX_Y;

		static const float CH_BAR_X_1P;
		static const float CH_BAR_X_2P;
		static const float CH_BAR_Y;

		static const float STG_BG_X;
		static const float STG_BG_Y;
		static const float TXT_STSL_X;
		static const float TXT_STSL_Y;
		static const float STG_X;
		static const float STG_Y;
		static const float STG_TRI_X;
		static const float STG_TRI_Y;

		static const float BGM_SCROLL_X;
		static const float BGM_SCROLL_Y;
		static const float TXT_BGM_X;
		static const float TXT_BGM_Y;
		static const float BGM_X;
		static const float BGM_Y;
		static const float BGM_TRI_X;
		static const float BGM_TRI_Y;

		static const float INST_X;
		static const float INST_Y;

#pragma endregion
	};


}	//namespace GAME

