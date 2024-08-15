//=================================================================================================
//
//	コリジョン( ぶつかり 衝突 判定 )
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../ExeChara/Main/ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Collision : public TASK_VEC
	{
		//キャラエグゼ
		P_ExeChara		m_pExeChara1p;
		P_ExeChara		m_pExeChara2p;


	public:
		Collision ();
		Collision ( const Collision & rhs ) = delete;
		~Collision ();

		void SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p);

#if 0
		P_EfPart GetpEfPart () const { return m_efPart; }
		void Decision_EfPart ();

#endif // 0

		void Do ();


	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------
#if 0
		//ダッシュ関連判定
		bool DashDecision ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center );

		//攻撃枠 同士判定　(中心付)
		bool DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center);

		//相殺枠判定(中心付)
		bool DcsOffset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center);

		//エフェクトの相殺枠判定
		void DcsOffsetEf (PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect2p);

		//エフェクトのヒット枠判定
		bool DcsHitEf (PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower);


		//判定後にキャラに反映する
		void Propagate ();

#endif // 0
		//---------------------------------------

		//離れる方向かどうか
		bool LeaveDir ( bool dirRight, float pos0, float pos1 );
	};

	using P_Collision = std::shared_ptr < Collision >;


}	//namespace GAME

