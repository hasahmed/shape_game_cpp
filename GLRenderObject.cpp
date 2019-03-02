#include "shapegame"

using namespace shapegame;
std::ostream& operator<< (std::ostream& stream, const shapegame::GLRenderObject& rObj) {
	using namespace std;
	cout << "Vertex Attrib Index: " << rObj.vertexAttribIndex << endl;
	cout << "VAO: " << rObj.vao << endl;
	cout << "VBO: " << rObj.vbo << endl;
	cout << "Shader Program: " << rObj.shaderProg << endl;
	cout << "Verts: " << endl;

	cout << "[";
	for (int i = 0; i < rObj.verts.size(); i++) {
		cout << rObj.verts[i];
		if ((i + 1) % 3 == 0 && i != 0) {
			cout << "]" << endl << "[";
		} else {
			cout << ", ";
		}
	}
	return stream;
}
