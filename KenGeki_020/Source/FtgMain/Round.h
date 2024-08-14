//=================================================================================================
//
//	Round ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Round : public TASK_VEC
	{
		//目標ラウンド数 ( 2先 == best of 3 ) ( 10先 == best of 19 )
		UINT		m_targetRound { 2 };

		//ラウンド取得数
		UINT		m_round_1p { 0 };
		UINT		m_round_2p { 0 };

		P_Grp	m_roundDisp_1p;
		P_Ob	m_ob_1p0;
		P_Ob	m_ob_1p1;
		P_Grp	m_roundDisp_2p;
		P_Ob	m_ob_2p0;
		P_Ob	m_ob_2p1;

	public:
		Round ();
		Round ( const Round & rhs ) = delete;
		~Round ();

		void Init ();
		void Move ();

		void SetRound_1p ( UINT i );
		void AddRound_1p ();
		void SetRound_2p ( UINT i );
		void AddRound_2p ();

		//試合(マッチ)終了判定
		bool IsEndMutch ();

		void On ();
		void Off ();

	private:
		static const float POS_BY;
		static const float POS_BX10;
		static const float POS_BX11;
		static const float POS_BX20;
		static const float POS_BX21;
	};

	using P_Round = std::shared_ptr < Round >;


}	//namespace GAME


