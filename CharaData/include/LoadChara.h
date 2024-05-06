//=================================================================================================
//
// LoadChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "IOCharaDefine.h"
#include "LoadCharaFunc.h"
#include "LoadCharaUtl.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------
	// .datファイルからCharaを読み込む
	//------------------------------------------------------
	class LoadChara
	{
		//try用
		void _Load ( const tstring & filename,  Chara & chara );

		//内部使用関数群
		LoadCharaFunc	m_func;
		LoadCharaUtl	m_utl;

	public:
		LoadChara ( const tstring & filename,  Chara & chara );
		LoadChara ( const LoadChara& rhs ) = delete;
		~LoadChara ();
	};


}	//namespace GAME


