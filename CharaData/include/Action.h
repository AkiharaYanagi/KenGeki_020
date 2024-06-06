//=================================================================================================
//
//	Action ヘッダファイル
//		スクリプトの一連、固有の値を追加
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Chara_Const.h"
#include "Sequence.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//==================================================================================
	//	◆アクション属性
	//		STAND, MOVE, DASH, ATTACK_L, ATTACK_M, ATTACK_H,
	//		CLANG, AVOID, DOTTY, DAMAGED, DEMO, OTHER
	//
	//==================================================================================

	//================================================================
	//	アクション		各フレームのスクリプトリストを持つ
	//		┣[]スクリプト
	//		┣次アクション
	//		┣消費バランス値
	//		┣アクション体勢
	//		┣アクション属性
	//================================================================
	
	class Action : public Sequence
	{
		ACTION_CATEGORY		m_category;		//アクション属性
		ACTION_POSTURE		m_posture;		//アクション体勢
		UINT				m_hitNum;		//ヒット数
		UINT				m_hitPitch;		//ヒット間隔
		int					m_balance;		//バランス値

	public:
		Action ();
		Action ( const Action & rhs ) = delete;
		~Action ();

		//アクション属性
		ACTION_CATEGORY GetCategory () const { return m_category; }
		void SetCategory ( ACTION_CATEGORY category ) { m_category = category; }

		//アクション体勢
		ACTION_POSTURE GetPosture () const { return m_posture; }
		void SetPosture ( ACTION_POSTURE posture ) { m_posture = posture; }

		//ヒット数
		UINT GetHitNum () const { return m_hitNum; }
		void SetHitNum ( UINT n ) { m_hitNum = n; }

		//ヒット間隔
		UINT GetHitPitch () const { return m_hitPitch; }
		void SetHitPitch ( UINT n ) { m_hitPitch = n; }

		//バランス値
		int GetBalance () { return m_balance; }
		void SetBalance ( int i ) { m_balance = i; }
};

	using P_Action = std::shared_ptr < Action >;
	using VP_Action = std::vector < P_Action >;
	using PVP_Action = std::shared_ptr < VP_Action >;

	using AUP_P_Action = std::unique_ptr < P_Action [] >;

	using AP_Action = s3d::Array < P_Action >;
	using PAP_Action = std::shared_ptr < AP_Action >;


}	//namespace GAME


