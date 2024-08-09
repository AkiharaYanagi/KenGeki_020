﻿//=================================================================================================
//
//	EfClang ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfClang.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfClang::EfClang ()
	{
		AddTexture ( U"Ef_Clang.png" );
	}

	EfClang::~EfClang ()
	{
	}

	void EfClang::Move ()
	{
		GameGraphic::Move ();
	}

	void EfClang::On ( VEC2 center )
	{
	}

#if 0

	void EfClang::Move ()
	{
		SetDispBase ( G_BASE_POS () );
		GrpEf::Move ();
	}

	void EfClang::On ( VEC2 center )
	{
		SetRevised ( center );
		SetFadeOut ( 30 );
		SetValid ( T );
		GrpEf::On ();
	}

#endif // 0
}
