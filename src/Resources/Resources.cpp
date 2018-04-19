#include "Resources.h"

Resources::Resources()
{
}

void Resources::Initialize()
{
	CompileShaders();
	LinkShaderPrograms();

	LoadTracks();

	LoadMeshLayouts();
	LoadMeshes();
	LoadTextures();
}

const std::unique_ptr<Track>& Resources::GetTrack() const
{
	return track;
}

void Resources::CompileShaders()
{
	Set(ShaderSourceId::MAIN_VERTEX, std::make_unique<ShaderSource>("vertex_shader.glsl", gl::GLenum::GL_VERTEX_SHADER));
	Set(ShaderSourceId::MAIN_FRAGMENT, std::make_unique<ShaderSource>("fragment_shader.glsl", gl::GLenum::GL_FRAGMENT_SHADER));
	Set(ShaderSourceId::PBR_VERTEX, std::make_unique<ShaderSource>("pbr_vertex.glsl", gl::GLenum::GL_VERTEX_SHADER));
	Set(ShaderSourceId::PBR_FRAGMENT, std::make_unique<ShaderSource>("pbr_fragment.glsl", gl::GLenum::GL_FRAGMENT_SHADER));
}

void Resources::LinkShaderPrograms()
{
	Set(ShaderProgramId::MAIN, 
		std::make_unique<ShaderProgram>(
			Get(ShaderSourceId::MAIN_VERTEX)->GlId(),
			Get(ShaderSourceId::MAIN_FRAGMENT)->GlId()
		));

	Set(ShaderProgramId::PBR,
		std::make_unique<ShaderProgram>(
			Get(ShaderSourceId::PBR_VERTEX)->GlId(),
			Get(ShaderSourceId::PBR_FRAGMENT)->GlId()
			));
}

void Resources::LoadTracks()
{
	track = std::make_unique<Track>(5000);
	std::cout << "Track generated, segmentCount: " << track->SegmentCount() << std::endl;
}

void Resources::LoadMeshLayouts()
{
	Set(
		MeshLayoutId::SIMPLE_TEXTURED, 
		std::make_unique<MeshLayout>(
			std::initializer_list<VertexAttribute>({ 
				VertexAttribute::POSITION, 
				VertexAttribute::UV })
			)
		);

	Set(
		MeshLayoutId::PBR,
		std::make_unique<MeshLayout>(
			std::initializer_list<VertexAttribute>({
		VertexAttribute::POSITION,
		VertexAttribute::UV,
		VertexAttribute::NORMAL,
		VertexAttribute::TANGENT,
		VertexAttribute::BITANGENT })
			)
		);
}

void Resources::LoadMesh(std::string filename, MeshId id, MeshLayoutId layoutId)
{
	Assimp::Importer importer;

	const unsigned int rvcFlags =
		aiComponent_COLORS |
		aiComponent_BONEWEIGHTS |
		aiComponent_ANIMATIONS |
		aiComponent_LIGHTS |
		aiComponent_CAMERAS |
		aiComponent_MATERIALS;
	importer.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, rvcFlags);

	const unsigned int sbpRemoveFlags =
		aiPrimitiveType_POINT |
		aiPrimitiveType_LINE;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, sbpRemoveFlags);

	const aiScene *scene = importer.ReadFile(
		Constants::RESOURCE_PATH + "Models/" + filename,
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_Triangulate |
		aiProcess_RemoveComponent |
		aiProcess_GenNormals |
		aiProcess_PreTransformVertices |
		aiProcess_ValidateDataStructure |
		aiProcess_SortByPType |
		aiProcess_FindDegenerates |
		aiProcess_OptimizeMeshes |
		aiProcess_OptimizeGraph
		);

	std::string errorString = importer.GetErrorString();
	if (!errorString.empty())
	{
		std::cout << "Asset import error: " << errorString << std::endl;
	}
	else
	{
		std::cout << "Asset import successfull\n";
	}

	std::cout << "Imported scene has " << scene->mNumMeshes << " meshes\n";
	std::cout << "Root node name: " << scene->mRootNode->mName.C_Str() << std::endl;
	const unsigned int meshId = scene->mRootNode->mMeshes[0];
	std::cout << "Mesh id: " << meshId << std::endl;
	aiMesh *mesh = scene->mMeshes[meshId];
	std::cout << "Vertices: " << mesh->mNumVertices << std::endl;
	std::cout << "Triangles: " << mesh->mNumFaces << std::endl;

	Set(id, std::make_unique<Mesh>(mesh, *Get(layoutId)));
}

void Resources::LoadMeshes()
{
	LoadPrimitiveMeshes();
	LoadMesh("tramwaj.fbx", MeshId::TRAM, MeshLayoutId::SIMPLE_TEXTURED);
	LoadMesh("cabinet.fbx", MeshId::CABINET, MeshLayoutId::PBR);
	Set(MeshId::TRACK, std::make_unique<Mesh>(*track));
}

void Resources::LoadPrimitiveMeshes()
{
	std::vector<float> vertices = {
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23
	};

	Set(MeshId::CUBE, std::make_unique<Mesh>(vertices, indices));

	vertices = std::vector<float>{
		-1, -1, 0,	0, 0,
		-1, 1, 0,	0, 1,
		1, 1, 0,	1, 1,
		1, -1, 0,	1, 0
	};

	indices = std::vector<unsigned int>{
		0, 1, 2,
		0, 2, 3
	};

	Set(MeshId::PLANE, std::make_unique<Mesh>(vertices, indices));
}

void Resources::LoadTextures()
{
	std::vector<std::pair<TextureId, std::string>> tuples{
		{ TextureId::CRATE, "crate.jpg" },
		{ TextureId::TRAM, "tram.png" },
		{ TextureId::TRACK, "track.jpg" },
		{ TextureId::SPEEDOMETER, "speedometer.png" },
		{ TextureId::SPEEDOMETER_TIP, "speedometer_tip.png" },
		{ TextureId::CABINET_ALBEDO, "test/cabinet_Cabinet_AlbedoTransparency.png" },
		{ TextureId::CABINET_METALLIC, "test/cabinet_Cabinet_MetallicSmoothness.png" },
		{ TextureId::CABINET_NORMAL, "test/cabinet_Cabinet_Normal.png" }
	};

	for(auto&& i : tuples)
	{
		Set(i.first, std::make_unique<Texture>(i.second));
	}
}

