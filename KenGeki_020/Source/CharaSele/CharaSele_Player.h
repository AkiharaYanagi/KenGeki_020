//=================================================================================================
//
//	CharaSele Player ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSeleConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaSele_Player : public TASK_VEC
	{
		PLAYER_ID		m_player_id { PLAYER_ID_1 };	//プレイヤ識別
		CHARA_SELE_ID	m_chsl_id { CHSLID_00 };			//キャラ選択ID
		P_Grp			m_chara_stand;					//キャラ立絵
		P_Grp			m_chara_stand_light;			//キャラ立絵(明度)
		P_Grp			m_chara_stand_shade;			//キャラ立絵(影)
		P_Grp			m_chara_name;					//キャラ名前
		P_GrpBlink		m_cursor;						//カーソル
		bool			m_decided { F };				//決定
		static const ChSlct		m_pos [ CHARA_SELE_NUM ];	//枠位置
		float			m_x { 0 };		//カットイン位置
		UINT			m_wait { 0 };	//決定ウェイト

	public:
		CharaSele_Player ();
		CharaSele_Player ( const CharaSele_Player & rhs ) = delete;
		~CharaSele_Player ();

		void PlayerInit ( PLAYER_ID id );

		void Move ();

		CHARA_SELE_ID GetID () const { return m_chsl_id; }
		CHARA_NAME GetName () const;

		bool IsDecided () const { return m_decided; }

	private:
		void SetCursorUp ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorDown ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorLeft ( P_GrpBlink pCrs, CHARA_SELE_ID & id );
		void SetCursorRight ( P_GrpBlink pCrs, CHARA_SELE_ID & id );

		void Input ();	//入力
		void Input_Decided ();		//決定後の入力
		void Cancel ();	//キャンセル
		void Select ();	//カーソル移動で選択時
		void Decide ();	//決定時

		bool CanSelect ();	//選択可能かどうか
		void SetCharaStand ( CHARA_SELE_ID id );
		void HiddenCharaStand ();
	};


	using P_ChSele_Pl = std::shared_ptr < CharaSele_Player >;


}	//namespace GAME


