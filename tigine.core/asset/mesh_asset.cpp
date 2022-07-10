#include "mesh_asset.h"

#include <assimp/Importer.hpp>
#include <assimp/include/assimp/postprocess.h>

namespace tigine {
	mesh_asset* mesh_asset::load(const std::string path) {
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

		mesh_asset* ret = new mesh_asset();
		return ret;
	}
}