//=================================================================================================
//
//	EfHitLine ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfHitLine.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfHitLine::EfHitLine ()
	{
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\00.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\01.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\02.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\03.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\04.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\05.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\06.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\07.png" );
		AddTexture_FromArchive ( U"Ef_Hit_Line0\\08.png" );
		SetBase ( VEC2 ( 0, 0 ) );
		SetRevised ( VEC2 ( -750, -500 ) );
		SetColor ( _CLR ( 0xffffffff ) );
		SetZ ( Z_EFF );
		SetShader ( T );
//		SetShader ( F );
	}

	EfHitLine::~EfHitLine ()
	{
	}

	void EfHitLine::Init ()
	{
		SetValid ( T );
	}

	void EfHitLine::Move ()
	{
	}


}
