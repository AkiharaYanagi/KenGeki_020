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

		//CharaImg
		//P_ChSl_Img		m_img_1p;
		//P_ChSl_Img		m_img_2p;

		//Player
		P_ChSl_Pl		m_player_1p;
		P_ChSl_Pl		m_player_2p;

	public:
		_CharaSele ();
		_CharaSele ( const _CharaSele & rhs ) = delete;
		~_CharaSele ();

		void ParamInit ();
		void Load ();
		P_GameScene Transit ();
	};


}	//namespace GAME

