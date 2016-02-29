from __future__ import division
from mmtbx.command_line.geometry_minimization import get_geometry_restraints_manager
import iotbx.pdb
import sys
import mmtbx.utils
from scitbx.array_family import flex

exclude_selection_string_for_3j7x = "not ((chain A and resid 18:20) or (chain A and resid 199:201) or (chain B and resid 44:46) or (chain B and resid 117:119) or (chain B and resid 198:200) or (chain B and resid 199:201) or (chain B and resid 205:207) or (chain B and resid 231:233) or (chain B and resid 238:240) or (chain B and resid 241:243) or (chain B and resid 295:297) or (chain C and resid 18:20) or (chain C and resid 117:119) or (chain C and resid 238:240) or (chain C and resid 243:245) or (chain C and resid 280:282) or (chain C and resid 297:299) or (chain D and resid 117:119) or (chain D and resid 141:143) or (chain D and resid 199:201) or (chain D and resid 295:297) or (chain E and resid 17:19) or (chain E and resid 18:20) or (chain E and resid 117:119) or (chain E and resid 199:201) or (chain E and resid 234:236) or (chain E and resid 235:237) or (chain E and resid 238:240) or (chain E and resid 295:297) or (chain F and resid 18:20) or (chain F and resid 117:119) or (chain F and resid 177:179) or (chain F and resid 178:180) or (chain F and resid 199:201) or (chain F and resid 205:207) or (chain F and resid 238:240) or (chain F and resid 246:248) or (chain F and resid 295:297) or (chain G and resid 51:53) or (chain G and resid 155:157) or (chain G and resid 203:205) or (chain G and resid 231:233) or (chain G and resid 233:235) or (chain G and resid 297:299))"


def minimize_hierarchy(hierarchy, xrs, original_pdb_h,
    excl_string_selection, log=None):
  from mmtbx.monomer_library.pdb_interpretation import grand_master_phil_str
  from mmtbx.refinement.geometry_minimization import run2
  from mmtbx.geometry_restraints import reference

  if log is None:
    # log = null_out()
    log = sys.stdout
  params_line = grand_master_phil_str
  params = iotbx.phil.parse(
      input_string=params_line, process_includes=True).extract()
  params.pdb_interpretation.clash_guard.nonbonded_distance_threshold=None
  params.pdb_interpretation.peptide_link.ramachandran_restraints = True
  params.pdb_interpretation.nonbonded_weight = 500
  # params.pdb_interpretation.peptide_link.oldfield.weight_scale=3
  # params.pdb_interpretation.peptide_link.oldfield.plot_cutoff=0.03
  params.pdb_interpretation.c_beta_restraints=True

  processed_pdb_files_srv = mmtbx.utils.\
      process_pdb_file_srv(
          crystal_symmetry= xrs.crystal_symmetry(),
          pdb_interpretation_params = params.pdb_interpretation,
          stop_for_unknowns         = False,
          log=log,
          cif_objects=None)
  processed_pdb_file, junk = processed_pdb_files_srv.\
      process_pdb_files(raw_records=flex.split_lines(hierarchy.as_pdb_string()))
  grm = get_geometry_restraints_manager(
      processed_pdb_file, xrs)

  print "Runnning first minimization"
  obj = run2(
      restraints_manager       = grm,
      pdb_hierarchy            = hierarchy,
      correct_special_position_tolerance = 1.0,
      max_number_of_iterations = 300,
      number_of_macro_cycles   = 5,
      bond                     = True,
      nonbonded                = True,
      angle                    = True,
      dihedral                 = True,
      chirality                = True,
      planarity                = True,
      fix_rotamer_outliers     = True,
      log                      = log)



  asc = original_pdb_h.atom_selection_cache()
  sel = asc.selection(excl_string_selection)


  grm.geometry.append_reference_coordinate_restraints_in_place(
      reference.add_coordinate_restraints(
          sites_cart = original_pdb_h.atoms().extract_xyz().select(sel),
          selection  = sel,
          sigma      = 0.5))


  print "Runnning second minimization"
  obj = run2(
      restraints_manager       = grm,
      pdb_hierarchy            = hierarchy,
      correct_special_position_tolerance = 1.0,
      max_number_of_iterations = 300,
      number_of_macro_cycles   = 5,
      bond                     = True,
      nonbonded                = True,
      angle                    = True,
      dihedral                 = True,
      chirality                = True,
      planarity                = True,
      fix_rotamer_outliers     = True,
      log                      = log)


def run(args):
  print args
  print args[0]
  print args[1]
  pdb_inp = iotbx.pdb.input(source_info=None, file_name=args[0])
  pdb_h = pdb_inp.construct_hierarchy()
  # print dir(pdb_inp)
  xrs = pdb_inp.xray_structure_simple()
  minimize_hierarchy(
      pdb_h,
      xrs,
      pdb_h.deep_copy(),
      # excl_string_selection=exclude_selection_string_for_3j7x,
      excl_string_selection="all",
      )
  pdb_h.write_pdb_file(file_name=args[1])


if (__name__ == "__main__"):
  print "__name__", __name__
  run(sys.argv[1:])