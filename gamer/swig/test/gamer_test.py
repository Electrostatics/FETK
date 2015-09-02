from gamer import *

# Read a surface mesh and Improve it
sm = SurfaceMesh("single-TT.off")
print "Num face markers", sm.nfm
sm.refine()
print "vertices:", sm.nv, "simplices:", sm.nf
sm.smooth()
sm.coarse_flat()
sm.coarse_dense()
sm.reset_face_markers()
sm.set_face_marker(0, 100)
sm.write_off("single-TT_improved.off")

sm = SurfaceMesh("1CID.pdb")

while not sm.smooth(20, 140, 1, True):
    pass

# Improve molecular surface
sm.coarse_flat()
sm.coarse_dense()
sm.smooth(20, 140, 10, True)
sm.normal_smooth()

# Get center information
atom = sm.get_center_radius()

# Generate sphere mesh
outer = SurfaceMesh(4)
ratio = 2.5
for i in xrange(outer.nv):
    outer.vertex(i).x = outer.vertex(i).x*atom.radius*ratio+atom.x;
    outer.vertex(i).y = outer.vertex(i).y*atom.radius*ratio+atom.y;
    outer.vertex(i).z = outer.vertex(i).z*atom.radius*ratio+atom.z;

merged = SurfaceMesh(sm, outer)

sm.write_off("some_molecule.off")
merged.write_off("some_merged_molecule.off")

gem_mesh = GemMesh(sm)
gem_mesh.write_off("molecular_volmesh.off")
