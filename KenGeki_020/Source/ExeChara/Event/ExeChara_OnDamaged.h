//=================================================================================================
//
//	ExeChara_OnDamaged
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
	//◆ 相手・攻撃 → 自分・くらい
	//くらい状態・ダメージ処理
	//==========================================
	class ExeChara_OnDamaged
	{
		WP_ExeChara		m_pSelf;		//自分キャラ(循環参照なのでweak_ptr)
		WP_ExeChara		m_pOther;		//相手キャラ(循環参照なのでweak_ptr)

		BtlParam &		m_btlPrm;		//バトルパラメータ参照
		P_Param			m_pParam;		//シーン共有パラメータ

	public:
		ExeChara_OnDamaged ( BtlParam & btlPrm );
		ExeChara_OnDamaged ( const ExeChara_OnDamaged & rhs ) = delete;
		~ExeChara_OnDamaged ();

		void SetEnvironment ( WP_ExeChara pSelf, WP_ExeChara pOther );
		void SetpParam ( P_Param p );


		//イベント：被ダメージ時
		void OnDamaged ();

		//ガード成立かどうか
		bool CheckGuard ();

		//ガードできる状態かどうか
		bool CanGuard () const;

		//ガード成立後の処理
		void OnGuard ();

		//相手ダメージ処理の後
		void OnDamaged_After ();

	};


}	//namespace GAME

