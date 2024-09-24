//=================================================================================================
//
// DispEffect ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../../GameMain/G_Ftg.h"
#include "../Disp/DispRect.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispEffect : public TASK_VEC
	{
		//P_Grp			m_grp;			//グラフィック表示
		P_GrpEfShd		m_grp;			//グラフィック表示
		PAP_Tx			mpap_EfTx;		//エフェクトイメージのテクスチャリスト
		P_DispRect		m_dispRect;		//エフェクト枠表示

		float		m_w { 1.f };		//幅

	public:
		DispEffect ( PAP_Tx papEfTx, float z );
		DispEffect ( const DispEffect & rhs ) = delete;
		~DispEffect ();

		//元データの設定
		void SetpChara ( P_Chara pChara );


		//有効フラグ設定
		void SetValid ( bool b ) { m_grp->SetValid ( b ); }

		//更新
		void Update ( P_Script pScript, VEC2 ptEf, bool dirRight );

		//表示枠設定
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//枠表示
		void OnRect () { m_dispRect->OnRect (); }
		//枠非表示
		void OffRect () { m_dispRect->OffRect (); }

		//P_Grp GetpGrp () { return m_grp; }
		//P_GrpEfShd GetpGrp () { return m_grp; }

		void SetW ( float w ) { m_w = w; }
	};

	using P_DispEffect = std::shared_ptr < DispEffect >;


}	//namespace GAME


