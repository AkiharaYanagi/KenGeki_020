//=================================================================================================
//
//	Fighting ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/Scene.h"
#include "BG.h"
#include "MutualChara.h"

#if 0

#include "FtgDemo.h"
#include "FtgGrp.h"

#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//	using WP_FTG = std::weak_ptr < Fighting >;

	class Fighting : public TASK_LST
	{
		//=====================================================
		//背景
		P_BG		m_bg;

		//test EF
		P_Grp		m_grp;

		//=====================================================
		//キャラ相互処理
		P_MutualChara	m_mutualChara;
#if 0

		//=====================================================
		//デモ
		P_FtgDemoActor	m_demoActor;
		bool			m_demoSkip;	//スキップ

		//=====================================================
		//画面共通グラフィック処理
		P_FtgGrp		m_pFtgGrp ;

#endif // 0

	public:
		Fighting ();
		Fighting ( const Fighting & rhs ) = delete;
		~Fighting ();

		void Init ();
		void Load ();
		void Move ();

		void ParamInit ( P_Param pParam );

#if 0
		bool IsEnd () const { return m_demoActor->IsEnd (); }

		//初期操作 プレイヤ/CPU 設定
		void Set_1P_vs_2P () { m_mutualChara->Set_1P_vs_2P (); }
		void Set_1P_vs_CPU () { m_mutualChara->Set_1P_vs_CPU (); }
		void Set_CPU_vs_CPU () { m_mutualChara->Set_CPU_vs_CPU (); }

		//初期デモスキップ設定
		void SetDemoOn () { m_demoSkip = F; }
		void SetDemoSkip () { m_demoSkip = T; }

		//トレーニング用リスタート
		void TrainingRestart ();

		//壁割り演出
		void WallBreak_L () { m_bg->StartWallBreak_L (); }
		void WallBreak_R () { m_bg->StartWallBreak_R (); }

		//下位オブエジェクトにweak_ptrを渡す
//		void AssignWp ( WP_FTG wp ) const;

	private:
		//共通グラフィック処理
		void Grp ();
#endif // 0
	};

	using P_FTG = std::shared_ptr < Fighting >;


}	//namespace GAME


