#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	// この頂点配列をアクティブにする (描画できるようにする)
	void SetActive();

	unsigned int GetNumIndices()const { return mNumIndices; }
	unsigned int GetNumVertes()const { return mNumVerts; }

private:
	// 頂点バッファにある頂点数
	unsigned int mNumVerts;

	// インデックスバッファにあるインデックス数
	unsigned int mNumIndices;
	// 頂点バッファ
	unsigned int mVertexBuffer;
	// インデックスバッファのopenGLID
	unsigned int mIndexBuffer;
	// 頂点配列のオブジェクトOpenGL	ID
	unsigned int mVertexArray;


};

