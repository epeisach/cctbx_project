from libtbx import test_utils
import libtbx.load_env

def run():
  tst_list = (
  "$B/array_family/tst_af_1",
  "$B/array_family/tst_af_2",
  "$B/array_family/tst_af_3",
  "$B/array_family/tst_af_4",
  "$B/array_family/tst_af_5",
  "$B/array_family/tst_vec3",
  "$B/array_family/tst_unsigned_float_arithmetic",
  "$B/array_family/tst_mat3",
  "$B/array_family/tst_sym_mat3",
  "$B/array_family/tst_ref_matrix_facet",
  "$B/array_family/tst_accessors",
  "$B/array_family/tst_optional_copy",
  "$B/serialization/tst_base_256",
  "$B/math/tests/tst",
  "$B/matrix/tests/tst_givens",
  "$B/matrix/tests/tst_householder",
  "$B/matrix/tests/tst_svd",
  "$B/matrix/tests/tst_cholesky",
  "$B/lstbx/tests/tst_normal_equations",
  "$D/linalg/tests/tst_matrix.py",
  "$D/linalg/tests/tst_cholesky.py",
  "$D/linalg/tests/tst_svd.py",
  "$D/linalg/tests/tst_eigensystem.py",
  "$D/error/tst_error.py",
  "$D/stl/tst_map.py",
  "$D/stl/tst_set.py",
  "$D/stl/tst_vector.py",
  "$D/array_family/boost_python/regression_test.py",
  "$D/array_family/boost_python/tst_flex.py",
  "$D/array_family/boost_python/tst_smart_selection.py",
  "$D/array_family/boost_python/tst_shared.py",
  "$D/array_family/boost_python/tst_integer_offsets_vs_pointers.py",
  "$D/array_family/boost_python/tst_cost_of_m_handle_in_af_shared.py",
  "$D/matrix.py",
  "$D/python_utils/tst_random_transform.py",
  "$D/python_utils/tst_graph.py",
  #*** Has someone forgot to add those here? ***
  #"$D/math/tests/tst_exp_functions.py",
  #"$D/math/tests/tst_fit_quadratic_function.py",
  "$D/math/tests/tst_gcd.py",
  "$D/math/tests/tst_math.py",
  "$D/math/tests/tst_r3_rotation.py",
  "$D/math/tests/tst_resample.py",
  "$D/math/tests/tst_line_search.py",
  "$D/math/tests/tst_gaussian.py",
  "$D/math/tests/tst_quadrature.py",
  "$D/math/tests/tst_halton.py",
  "$D/math/tests/tst_euler_angles.py",
  "$D/math/tests/tst_superpose.py",
  "$D/math/sieve_of_eratosthenes.py",
  "$D/math/besselk.py",
  "$D/math/scale_curves.py",
  "$D/math/tests/tst_fit_peak.py",
  "$D/minpack/tst.py",
  ["$D/lbfgs/tst_ext.py"],
  "$D/lbfgs/tst_lbfgs_f.py",
  "$B/lbfgs/tst_lbfgs",
  "$D/lbfgsb/boost_python/tst_lbfgsb.py",
  ["$D/fftpack/boost_python/tst_fftpack.py"],
  "$D/examples/flex_grid.py",
  "$D/examples/flex_array_loops.py",
  "$D/examples/principal_axes_of_inertia.py",
  "$D/examples/lbfgs_recipe.py",
  "$D/examples/lbfgs_linear_least_squares_fit.py",
  "$D/examples/chebyshev_lsq_example.py",
  "$D/examples/immoptibox_ports.py",
  "$D/examples/rigid_body_refinement_core.py",
  "$D/examples/integrating_a_weighted_sinc_function.py",
  "$D/graph/tst_utils.py",
  "$D/graph/rigidity.py",
  "$D/graph/tst_rigidity.py",
  "$D/graph/rigidity_matrix_symbolic.py",
  "$D/graph/tst_tardy_tree_find_paths.py",
  "$D/graph/tst_tardy_tree.py",
  "$D/rigid_body/essence/tst_basic.py",
  "$D/rigid_body/essence/tst_tardy.py",
  "$D/rigid_body/essence/tst_energy_plots.py",
  "$D/rigid_body/tst.py",
  "$D/rigid_body/proto/free_motion_reference_impl.py",
  "$D/rigid_body/proto/tst_featherstone.py",
  "$D/rigid_body/proto/tst_free_motion.py",
  "$D/rigid_body/proto/tst_free_motion_hard.py",
  "$D/rigid_body/proto/tst_joint_lib.py",
  "$D/rigid_body/proto/tst_singular.py",
  "$D/rigid_body/proto/tst_spherical_refinement.py",
  "$D/rigid_body/proto/tst_molecules.py",
  "$D/sparse/tests/tst_sparse.py",
  "$D/sparse/tests/tst_lu_factorization.py",
  "$D/iso_surface/tst_iso_surface.py",
  "$B/fortran_io/tests/tst_numeric_manipulators",
  "$B/fortran_io/tests/tst_numeric_parsers",
  "$D/simplex.py",
  "$D/differential_evolution.py",
  "$D/golden_section_search.py",
  "$D/direct_search_simulated_annealing.py",
  "$D/random/tests/tst_random.py",
  )

  build_dir = libtbx.env.under_build("scitbx")
  dist_dir = libtbx.env.dist_path("scitbx")

  test_utils.run_tests(build_dir, dist_dir, tst_list)

if (__name__ == "__main__"):
  run()
