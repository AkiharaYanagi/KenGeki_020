//=================================================================================================
//
//	_CharaSele Player ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSeleConst.h"
#include "../GameMain/Param.h"
#include "CharaSele_Image.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele_Player : public TASK_VEC
	{
		P_Param			m_pParam;
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラ選択ID
		P_ChSl_Img		m_chara_img;	//キャラ立絵

	public:
		_CharaSele_Player ();
		_CharaSele_Player ( const _CharaSele_Player & rhs ) = delete;
		~_CharaSele_Player ();

		void LoadTx ( P_ChSl_Img_Cmn pCmn );
		void ParamInit ( P_Param p );
		void PlayerInit ( PLAYER_ID id );

		void Move ();
	};

	using P_ChSl_Pl = std::shared_ptr < _CharaSele_Player >;


}	//namespace GAME


