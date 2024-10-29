//=================================================================================================
//
//	Branch ヘッダファイル
//		スクリプト遷移条件の入力コマンドと遷移先シークエンス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "Chara_Const.h"
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//---------------------------------------------------------------
	//前方宣言
	class Sequence;
	using P_Sqc = std::shared_ptr < Sequence >;
	using WP_Sqc = std::weak_ptr < Sequence >;		//循環参照

	using VP_Sqc = std::vector < P_Sqc >;
	using PVP_Sqc = std::shared_ptr < VP_Sqc >;
	using WP_Command = std::weak_ptr < Command >;		//循環参照

	//---------------------------------------------------------------
	class Branch
	{
//		tstring		m_name;				//名前
		s3d::String		m_name;				//名前
		BRANCH_CONDITION		m_condition;	//分岐条件

		UINT		m_indexCommand;		//条件コマンド配列添字
//		tstring		m_nameCommand { _T("cmd_name") };	//条件コマンド名前
		s3d::String m_nameCommand { U"cmd_name" };	//条件コマンド名前
		WP_Command	m_pCommand;			//条件コマンドポインタ

		UINT		m_indexSequence;	//遷移先シークエンス添字
//		tstring		m_nameSequence { _T("sqc_name") };	//遷移先シークエンス名前
		s3d::String	m_nameSequence { U"sqc_name" };	//遷移先シークエンス名前
		WP_Sqc		m_pSequence;		//遷移先シークエンスポインタ

		UINT		m_indexFrame;		//遷移先スクリプト位置
		bool		m_ohter;			//同一シークエンスで遷移可能かどうか

	public:
		Branch ();
		Branch ( const Branch & rhs ) = delete;
		~Branch ();

		//名前
//		tstring GetName () const { return m_name; }
//		void SetName ( tstring name ) { m_name.assign ( name ); }
		s3d::String GetName () const { return m_name; }
		void SetName ( s3d::String name ) { m_name.assign ( name ); }

		//分岐条件
		void SetCondition ( BRANCH_CONDITION bc ) { m_condition = bc; }
		BRANCH_CONDITION GetCondition () const { return m_condition; }

		//条件コマンド配列添字
		void SetIndexCommand ( UINT index ) { m_indexCommand = index; }
		UINT GetIndexCommand () const { return m_indexCommand; }

		//条件コマンドポインタ
		void SetpCommand ( P_Command pCommand ) { m_pCommand = pCommand; }
		WP_Command GetpCommand () const { return m_pCommand; }

		//条件コマンド名
		s3d::String GetNameCommand () const { return m_nameCommand; }
		void SetNameCommand ( s3d::String name ) { m_nameCommand.assign ( name ); }

		//遷移先シークエンス配列添字
		void SetIndexSequence ( UINT index ) { m_indexSequence = index; }
		UINT GetIndexSequence () const { return m_indexSequence; }

		//遷移先シークエンスポインタ
		void SetpSequence ( P_Sqc pAction ) { m_pSequence = pAction; }
		WP_Sqc GetpSequence () const { return m_pSequence; }

		//遷移先シークエンス名
		s3d::String GetNameSequence () const { return m_nameSequence; }
		void SetNameSequence ( s3d::String name ) { m_nameSequence.assign ( name ); }

		//遷移先スクリプト位置
		void SetIndexFrame ( UINT index ) { m_indexFrame = index; }
		UINT GetIndexFrame () const { return m_indexFrame; }

		//同一で遷移
		void SetOther ( bool b ) { m_ohter = b; }
		bool GetOther () const { return m_ohter; }
	};


	using P_Branch = std::shared_ptr < Branch >;
	using VP_Branch = std::vector < P_Branch >;
	using PVP_Branch = std::shared_ptr < VP_Branch >;


}	//namespace GAME


