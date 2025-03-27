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

	class _CharaSele_Actor	: public GameTaskVector
	{
		//現在のステート
		P_ChSl_St	m_state;

		//各種ステート
		P_ChSlSt_Ch		m_state_Ch;
		P_ChSlSt_Clr	m_state_Clr;
		P_ChSlSt_Stg	m_state_Stg;
		P_ChSlSt_BGM	m_state_BGM;
		P_ChSlSt_OK		m_state_OK;


	public:
		_CharaSele_Actor ();
		_CharaSele_Actor ( const _CharaSele_Actor & rhs ) = delete;
		~_CharaSele_Actor ();

		//状態変更
		void Start_Ch ();
		void Start_Clr ();
		void Start_Stg ();
		void Start_BGM ();
		void Start_OK ();
	};


}	//namespace GAME

