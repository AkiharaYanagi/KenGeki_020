//=================================================================================================
//
//	_CharaSele_Actor
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "_CharaSele_State.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class _CharaSele_Actor	: public TASK_VEC, public std::enable_shared_from_this < _CharaSele_Actor >
	{
		//現在のステート
		P_ChSl_St	m_state;

		//各種ステート
		P_ChSlSt_Ch		m_state_Ch;
		P_ChSlSt_Clr	m_state_Clr;
		P_ChSlSt_Stg	m_state_Stg;
		P_ChSlSt_BGM	m_state_BGM;
		P_ChSlSt_OK		m_state_OK;

		//すべてのステート
		s3d::Array < P_ChSl_St >	m_aryState;


	public:
		_CharaSele_Actor ();
		_CharaSele_Actor ( const _CharaSele_Actor & rhs ) = delete;
		~_CharaSele_Actor ();

		void PlayerInit ( PLAYER_ID id );
		void Load ();
		void Move ();

		void Input ();


		//状態変更
		void Start_Ch ();
		void Start_Clr ();
		void Start_Stg ();
		void Start_BGM ();
		void Start_OK ();

		bool Is_OK () const { return m_state_OK == m_state; }


		//参照
		void SetwpCharaSele ( WP_CharaSele wp );
		void SetwpChSl_Player ( WP_ChSl_Player wp );
		void SetpCursor ( P_ChSl_Cursor p );
	};

	using P_ChSl_Actor = std::shared_ptr < _CharaSele_Actor >;
	using WP_ChSl_Actor = std::weak_ptr < _CharaSele_Actor >;



}	//namespace GAME

