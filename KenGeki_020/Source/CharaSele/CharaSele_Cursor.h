//=================================================================================================
//
//	CharaSele_Cursor
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Param.h"
#include "CharaSeleConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class _CharaSele_Player; using WP_ChSl_Player = std::weak_ptr < _CharaSele_Player >;


	class CharaSele_Cursor	: public GameTaskVector
	{
		WP_ChSl_Player	mwp_player;	//親

		P_GrpBlink		m_cursor;						//カーソル枠画像
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };		//キャラセレID

	public:
		CharaSele_Cursor ();
		CharaSele_Cursor ( const CharaSele_Cursor & rhs ) = delete;
		~CharaSele_Cursor ();

		void PlayerInit ( PLAYER_ID id );
		void ParamInit ( P_Param p );

		//参照
		void SetwpChSl_Player ( WP_ChSl_Player wp ) { mwp_player = wp; }

		void Input ();

		void SetChara ( CHARA_SELE_ID chsl_id );
		CHARA_NAME GetCharaName () const;

		void Up ();
		void Down ();
		void Left ();
		void Right ();

		void Start () { m_cursor->Start (); }
		void Stop () { m_cursor->Stop (); }

	private:
		VEC2 GetPos ( CHARA_SELE_ID chsl_id );
		void Select ();
	};

	using P_ChSl_Cursor = std::shared_ptr < CharaSele_Cursor >;


}	//namespace GAME

