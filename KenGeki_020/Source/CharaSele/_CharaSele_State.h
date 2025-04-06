//=================================================================================================
//
//	_CharaSele_State
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSele_Cursor.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//アクタ　前方宣言
	class _CharaSele; using WP_CharaSele = std::weak_ptr < _CharaSele >;
	class _CharaSele_Player; using WP_ChSl_Player = std::weak_ptr < _CharaSele_Player >;
	class _CharaSele_Actor; using WP_ChSl_Actor = std::weak_ptr < _CharaSele_Actor >;


	//=====================================================
	//基本ステート
	class _CharaSele_State	: public GameTaskVector
	{
	protected:
		WP_CharaSele	mwp_CharaSele;	//親の親の親
		WP_ChSl_Player	mwp_Player;	//親の親
		WP_ChSl_Actor	mwp_Actor;	//親アクタ
		PLAYER_ID		m_player_id { PLAYER_ID_2 };	//プレイヤ識別
		P_ChSl_Cursor	m_cursor;		//カーソル

	public:
		_CharaSele_State () {}
		_CharaSele_State ( const _CharaSele_State & rhs ) = delete;
		~_CharaSele_State () {}

		virtual void Move () {}
		virtual void Input () {}

		void SetwpCharaSele ( WP_CharaSele wp ) { mwp_CharaSele = wp; }
		void SetwpPlayer ( WP_ChSl_Player wp ) { mwp_Player = wp; }
		void SetwpActor ( WP_ChSl_Actor wp ) { mwp_Actor = wp; }

		void SetPlayerID ( PLAYER_ID id ) { m_player_id = id; }
		void SetpCursor ( P_ChSl_Cursor p ) { m_cursor = p; }
	};

	using ChSl_St = _CharaSele_State;
	using P_ChSl_St = std::shared_ptr < ChSl_St >;


	//=====================================================

	//キャラクタ選択
	class ChSl_St_Chara : public ChSl_St
	{
	public:
		void Move ();
		void Input ();
	private:
		void Decide ();
	};
	using P_ChSlSt_Ch = std::shared_ptr < ChSl_St_Chara >;


	//カラー選択
	class ChSl_St_Color : public ChSl_St
	{
	public:
		void Move ();
		void Input ();
	private:
		void Decide ();
		void Cancel ();
	};
	using P_ChSlSt_Clr = std::shared_ptr < ChSl_St_Color >;


	//ステージ選択
	class ChSl_St_Stage : public ChSl_St
	{
	public:
		void Move ();
		void Input ();
	private:
		void Decide ();
		void Cancel ();
	};
	using P_ChSlSt_Stg = std::shared_ptr < ChSl_St_Stage >;


	//BGM選択
	class ChSl_St_BGM : public ChSl_St
	{
	public:
		void Move ();
		void Input ();
	private:
		void Decide ();
		void Cancel ();
	};
	using P_ChSlSt_BGM = std::shared_ptr < ChSl_St_BGM >;


	//選択完了
	class ChSl_St_OK : public ChSl_St
	{
	public:
		void Move ();
		void Input ();
	private:
		void Cancel ();
	};
	using P_ChSlSt_OK = std::shared_ptr < ChSl_St_OK >;



}	//namespace GAME

