//=================================================================================================
//
//	デシジョン( 攻撃・当たり 判定)
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../ExeChara/Main/ExeChara.h"
#include "../../GameMain/Param.h"
#include "../Ef/EfClang.h"
#if 0
#include "Ef/EfSpark.h"
#include "Ef/EfParticle.h"
#include "Ef/EfPart.h"
#include "Ef/EfHit.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Decision : public TASK_VEC
	{
		//キャラエグゼ
		P_ExeChara		m_pExeChara1p;
		P_ExeChara		m_pExeChara2p;

		//パラメータ
		P_Param			m_pParam;

		//相殺ヒットストップ
		P_Timer			m_tmrOffset_Hitstop;

		//相殺回数
//		int32			m_nOffset { 0 };

		//共通エフェクト
		P_EfClang		m_efClang;
		P_GrpEf			m_efHit;

#if 0
		P_EfSpark		m_efSpark;
//		P_EfParticle	m_efParticle;
		P_EfPart		m_efPart;
#endif // 0

#if 0


		//---------------------------------
		//判定フラグ
//		bool		m_bOffsetChara;		//キャラ同士相殺
		bool		m_Efhit1P;		//エフェクトのヒットチェック
		bool		m_Efhit2P;		//エフェクトのヒットチェック
		bool		m_hit1P;		//本体ヒットフラグ
		bool		m_hit2P;		//本体ヒットフラグ
#endif // 0


	public:
		Decision ();
		Decision ( const Decision & rhs ) = delete;
		~Decision ();

		void SetpParam ( P_Param p ) { m_pParam = p; }
		void SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p);

		void Init ();
		void Load ();

#if 0
		P_EfPart GetpEfPart () const { return m_efPart; }
		void Decision_EfPart ();

#endif // 0

		void Do ();
#if 0


	private:
		//------------------------------------------------------
		//	内部関数
		//------------------------------------------------------
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
	};

	using P_Decision = std::shared_ptr < Decision >;


}	//namespace GAME

