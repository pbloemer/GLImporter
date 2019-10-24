from pyntcloud.io.ply import read_ply
from pyntcloud import PyntCloud
import json
import numpy as np
import sys

if __name__ == "__main__":
    ply = read_ply(sys.argv[1])
    comments = "blah blah"
    data_format = "triangles"
    data_len = len(ply['mesh']['v1'])
    v1 = np.ndarray((data_len, 3), dtype=np.float32)
    v2 = np.ndarray((data_len, 3), dtype=np.float32)
    v3 = np.ndarray((data_len, 3), dtype=np.float32)
    n = np.ndarray((data_len, 3), dtype=np.float32)
    normals = np.ndarray((data_len, 3))
    for i, _ in enumerate(ply['mesh']['v1']):
        v1[i] = [ply['points']['x'][ply['mesh']['v1'][i]], ply['points']['y'][ply['mesh']['v1'][i]],
                 ply['points']['z'][ply['mesh']['v1'][i]]]
        v2[i] = [ply['points']['x'][ply['mesh']['v2'][i]], ply['points']['y'][ply['mesh']['v2'][i]],
                 ply['points']['z'][ply['mesh']['v2'][i]]]
        v3[i] = [ply['points']['x'][ply['mesh']['v3'][i]], ply['points']['y'][ply['mesh']['v3'][i]],
                 ply['points']['z'][ply['mesh']['v3'][i]]]
        n[i] = [ply['points']['nx'][ply['mesh']['v3'][i]], ply['points']['ny'][ply['mesh']['v3'][i]],
                ply['points']['nz'][ply['mesh']['v3'][i]]]
    data = {"description": comments, "format": data_format, "geometry": {"v1": v1.tolist(), "v2": v2.tolist(),
                                                                         "v3": v3.tolist()}, "normals": n.tolist()}
    filename = sys.argv[1].split('.')[0] + '.json'
    file = open(filename, 'w')
    output = json.dump(data, file, sort_keys=True, indent=2)
    file.close()
