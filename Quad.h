#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Camera.h"
#include "Texture.h"

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[

struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;
};

class Quad
{
public:
	Quad();
	~Quad();
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();
private:
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;	//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	// �萔�o�b�t�@
	Texture* pTexture_;
};