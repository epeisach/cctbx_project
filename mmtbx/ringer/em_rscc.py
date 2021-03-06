
"""
Utility script to calculate per-residue RSCCs for a model versus an EM map with
an arbitrary origin.

Author: Nat Echols
Reference:
  Barad BA, Echols N, Wang RYR, Cheng YC, DiMaio F, Adams PD, Fraser JS.
  Side-chain-directed model and map validation for 3D Electron Cryomicroscopy.
  Manuscript in review.
"""

from __future__ import division
import iotbx.phil
from cctbx import crystal
from cctbx import maptbx
from scitbx.array_family import flex
import sys

master_phil_str = """
model = None
  .type = path
map = None
  .type = path
d_min = 3.0
  .type = float
  .help = Optional cutoff resolution for computing F(calc). This will not \
    affect the dimensions of the ultimate FC map.
atom_radius = 1.5
  .type = float
"""

def run(args, out=sys.stdout):
  cmdline = iotbx.phil.process_command_line_with_files(
    args=args,
    master_phil_string=master_phil_str,
    pdb_file_def="model",
    map_file_def="map",
    usage_string="""\
em_rscc.py model.pdb map.ccp4

%s""" % __doc__)
  params = cmdline.work.extract()
  assert (not None in [params.model, params.map])
  pdb_in = cmdline.get_file(params.model).file_object
  m = cmdline.get_file(params.map).file_object
  print >> out, "Input electron density map:"
  print >> out, "m.all()   :", m.data.all()
  print >> out, "m.focus() :", m.data.focus()
  print >> out, "m.origin():", m.data.origin()
  print >> out, "m.nd()    :", m.data.nd()
  print >> out, "m.size()  :", m.data.size()
  print >> out, "m.focus_size_1d():", m.data.focus_size_1d()
  print >> out, "m.is_0_based()   :", m.data.is_0_based()
  print >> out, "map: min/max/mean:", flex.min(m.data), flex.max(m.data), flex.mean(m.data)
  print >> out, "unit cell:", m.unit_cell_parameters
  symm = crystal.symmetry(
    space_group_symbol="P1",
    unit_cell=m.unit_cell_parameters)
  xrs = pdb_in.input.xray_structure_simple(crystal_symmetry=symm)
  print >> out, "Setting up electron scattering table (d_min=%g)" % params.d_min
  xrs.scattering_type_registry(
    d_min=params.d_min,
    table="electron")
  fc = xrs.structure_factors(d_min=params.d_min).f_calc()
  cg = maptbx.crystal_gridding(
    unit_cell=symm.unit_cell(),
    space_group_info=symm.space_group_info(),
    pre_determined_n_real=m.data.all())
  fc_map = fc.fft_map(
    crystal_gridding=cg).apply_sigma_scaling().real_map_unpadded()
  assert (fc_map.all() == fc_map.focus() == m.data.all())
  em_data = m.data.as_double()
  unit_cell_for_interpolation = m.grid_unit_cell()
  frac_matrix = unit_cell_for_interpolation.fractionalization_matrix()
  sites_cart = xrs.sites_cart()
  sites_frac = xrs.sites_frac()
  print >> out, "PER-RESIDUE CORRELATION:"
  for chain in pdb_in.hierarchy.only_model().chains():
    for residue_group in chain.residue_groups():
      i_seqs = residue_group.atoms().extract_i_seq()
      values_em = flex.double()
      values_fc = flex.double()
      for i_seq in i_seqs :
        rho_em = maptbx.non_crystallographic_eight_point_interpolation(
          map=em_data,
          gridding_matrix=frac_matrix,
          site_cart=sites_cart[i_seq])
        rho_fc = fc_map.eight_point_interpolation(sites_frac[i_seq])
        values_em.append(rho_em)
        values_fc.append(rho_fc)
      cc = flex.linear_correlation(x=values_em, y=values_fc).coefficient()
      print >> out, residue_group.id_str(), cc

if (__name__ == "__main__"):
  run(sys.argv[1:])
