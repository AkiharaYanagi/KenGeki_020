//=================================================================================================
//
//	ExeChara_OnHit
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../BtlParam.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	//前方宣言
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = std::weak_ptr < ExeChara >;
	//------------------------------------------------


	//==========================================
	//◆ 自分・攻撃 -> 相手・くらい
	//ヒット発生(攻撃成立側)
	//==========================================
	class ExeChara_OnHit
	{
		WP_ExeChara		m_pSelf;		//自分キャラ(循環参照なのでweak_ptr)
		WP_ExeChara		m_pOther;		//相手キャラ(循環参照なのでweak_ptr)

		BtlParam &		m_btlPrm;		//バトルパラメータ参照
		P_Param			m_pParam;		//シーン共有パラメータ

	public:
		ExeChara_OnHit ( BtlParam & btlPrm );
		ExeChara_OnHit ( const ExeChara_OnHit & rhs ) = delete;
		~ExeChara_OnHit ();

		void SetEnvironment ( WP_ExeChara pSelf, WP_ExeChara pOther );
		void SetpParam ( P_Param p );


		//イベント：与ダメージ時
		void OnHit ();


		//自分ノックバック処理
		void OnKnockBack ();

		//投げられ判定
		bool CanBeThrown () const;

#if 0
		//投げ判定
		bool IsThrowAction () const;

		//相殺しない判定
		bool IsNotOffset () const;
#endif // 0

		//エフェクトヒット発生(攻撃成立側)
		void OnEfHit ();
	};



}	//namespace GAME

