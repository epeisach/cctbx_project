// $Id$
/* Copyright (c) 2001 The Regents of the University of California through
   E.O. Lawrence Berkeley National Laboratory, subject to approval by the
   U.S. Department of Energy. See files COPYRIGHT.txt and
   cctbx/LICENSE.txt for further details.

   Revision history:
     Jul 2002: Created, based on fragments from sharedmodule.cpp (rwgk)
 */

#include <boost/python/cross_module.hpp>
#include <cctbx/bpl_utils.h>
#include <cctbx/miller_bpl.h>
#include <cctbx/hendrickson_lattman_bpl.h>
#include <cctbx/array_family/shared_bpl.h>
#include <cctbx/miller/sym_equiv.h>
#include <cctbx/miller/asu.h>
#include <cctbx/miller/build.h>
#include <cctbx/miller/span.h>
#include <cctbx/miller/join.h>
#include <cctbx/miller/expand.h>

namespace {

  using namespace cctbx;
  using namespace cctbx::miller;

  double SymEquivIndex_HT_angle_0(
    SymEquivIndex const& SEI)
  {
    return SEI.HT_angle();
  }

  SymEquivIndex
  SymEquivIndex_Mate_0(
    const SymEquivIndex& SEI)
  {
    return SEI.Mate();
  }

  double SymEquivIndex_phase_eq_1(
    const SymEquivIndex& SEI,
    double phi_in)
  {
    return SEI.phase_eq(phi_in);
  }
  double SymEquivIndex_phase_eq_2(
    const SymEquivIndex& SEI,
    double phi_in,
    bool deg)
  {
    return SEI.phase_eq(phi_in, deg);
  }
  double SymEquivIndex_phase_in_1(
    const SymEquivIndex& SEI,
    double phi_eq)
  {
    return SEI.phase_in(phi_eq);
  }
  double SymEquivIndex_phase_in_2(
    const SymEquivIndex& SEI,
    double phi_eq,
    bool deg)
  {
    return SEI.phase_in(phi_eq, deg);
  }
  std::complex<double>
  SymEquivIndex_complex_eq(
    const SymEquivIndex& SEI,
    const std::complex<double>& f_in)
  {
    return SEI.complex_eq(f_in);
  }
  std::complex<double>
  SymEquivIndex_complex_in(
    const SymEquivIndex& SEI,
    const std::complex<double>& f_eq)
  {
    return SEI.complex_in(f_eq);
  }
  hendrickson_lattman<double>
  SymEquivIndex_hl_eq(
    SymEquivIndex const& SEI,
    hendrickson_lattman<double> const& coeff_in)
  {
    return SEI.hl_eq(coeff_in);
  }
  hendrickson_lattman<double>
  SymEquivIndex_hl_in(
    SymEquivIndex const& SEI,
    hendrickson_lattman<double> const& coeff_eq)
  {
    return SEI.hl_in(coeff_eq);
  }

  SymEquivIndex
  SymEquivIndices_getitem(const SymEquivIndices& SEMI,
                                std::size_t key) {
    if (key >= SEMI.N()) bpl_utils::throw_index_out_of_range();
    return SEMI[key];
  }
  SymEquivIndex
  SymEquivIndices_call_1(const SymEquivIndices& SEMI,
                               int iIL) {
    return SEMI(iIL);
  }
  SymEquivIndex
  SymEquivIndices_call_2(const SymEquivIndices& SEMI,
                               int iInv, int iList) {
    return SEMI(iInv, iList);
  }
  bool
  SymEquivIndices_isValidPhase_2(const SymEquivIndices& SEMI,
                                       double phi, bool deg) {
    return SEMI.isValidPhase(phi, deg);
  }
  bool
  SymEquivIndices_isValidPhase_1(const SymEquivIndices& SEMI,
                                       double phi) {
    return SEMI.isValidPhase(phi);
  }

  Index
  IndexGenerator_getitem(IndexGenerator& MIG, std::size_t)
  {
    Index result = MIG.next();
    if (result.is000()) {
      PyErr_SetString(PyExc_IndexError, "End of list.");
      boost::python::throw_error_already_set();
    }
    return result;
  }

  af::shared<Index>
  py_BuildIndices_Resolution_d_min(
    const uctbx::UnitCell& UC,
    const sgtbx::SpaceGroupInfo& SgInfo,
    bool FriedelFlag,
    double Resolution_d_min)
  {
    af::shared<Index> result;
    IndexGenerator(
      UC, SgInfo, FriedelFlag, Resolution_d_min).AddToArray(result);
    return result;
  }
  af::shared<Index>
  py_BuildIndices_MaxIndex(
    const sgtbx::SpaceGroupInfo& SgInfo,
    bool FriedelFlag,
    const Index& MaxIndex)
  {
    af::shared<Index> result;
    IndexGenerator(
      SgInfo, FriedelFlag, MaxIndex).AddToArray(result);
    return result;
  }

  void
  py_expand_to_p1_4(
    sgtbx::SpaceGroup const& SgOps,
    bool friedel_flag,
    const af::shared<Index>& in,
    af::shared<Index>& out)
  {
    expand_to_p1(SgOps, friedel_flag, in, out);
  }

  void
  py_expand_to_p1_9(
    sgtbx::SpaceGroup const& SgOps,
    bool friedel_flag,
    af::shared<Index> const& h_in,
    af::shared<double> const& ampl_in,
    af::shared<double> const& phase_in,
    af::shared<Index> h_out,
    af::shared<double> ampl_out,
    af::shared<double> phase_out,
    bool phase_degrees)
  {
    expand_to_p1(
      SgOps, friedel_flag,
      h_in, ampl_in, phase_in,
      h_out, ampl_out, phase_out,
      phase_degrees);
  }
  void
  py_expand_to_p1_8(
    sgtbx::SpaceGroup const& SgOps,
    bool friedel_flag,
    af::shared<Index> const& h_in,
    af::shared<double> const& ampl_in,
    af::shared<double> const& phase_in,
    af::shared<Index> h_out,
    af::shared<double> ampl_out,
    af::shared<double> phase_out)
  {
    expand_to_p1(
      SgOps, friedel_flag,
      h_in, ampl_in, phase_in,
      h_out, ampl_out, phase_out);
  }

# include <cctbx/basic/from_bpl_import.h>

  void init_module(python::module_builder& this_module)
  {
    const std::string Revision = "$Revision$";
    this_module.add(ref(to_python(
        Revision.substr(11, Revision.size() - 11 - 2))), "__version__");

    python::import_converters<uctbx::UnitCell>
    py_UnitCell("cctbx_boost.uctbx", "UnitCell");

    python::import_converters<sgtbx::PhaseInfo>
    py_PhaseInfo("cctbx_boost.sgtbx", "PhaseInfo");

    python::import_converters<sgtbx::SpaceGroup>
    py_SpaceGroup("cctbx_boost.sgtbx", "SpaceGroup");

    python::import_converters<sgtbx::SpaceGroupInfo>
    py_SpaceGroupInfo("cctbx_boost.sgtbx", "SpaceGroupInfo");

    python::import_converters<sgtbx::ReciprocalSpaceASU>
    py_ReciprocalSpaceASU("cctbx_boost.sgtbx", "ReciprocalSpaceASU");

    python::import_converters<af::shared<std::complex<double> > >
    py_sh_complex_double("cctbx_boost.arraytbx.shared", "complex_double");

    python::import_converters<af::shared<double> >
    py_sh_double("cctbx_boost.arraytbx.shared", "double");

    python::import_converters<af::shared<size_t> >
    py_sh_size_t("cctbx_boost.arraytbx.shared", "size_t");

    python::import_converters<af::shared<af::tiny<size_t, 2> > >
    py_sh_tiny_size_t_2("cctbx_boost.arraytbx.shared", "tiny_size_t_2");

    python::import_converters<af::shared<Index> >
    py_sh_miller_Index("cctbx_boost.arraytbx.shared", "miller_Index");

    class_builder<SymEquivIndex>
    py_SymEquivIndex(this_module, "SymEquivIndex");

    class_builder<SymEquivIndices>
    py_SymEquivIndices(this_module, "SymEquivIndices");

    class_builder<IndexTableLayoutAdaptor>
    py_IndexTableLayoutAdaptor(this_module, "IndexTableLayoutAdaptor");

    class_builder<AsymIndex>
    py_AsymIndex(this_module, "AsymIndex");

    class_builder<IndexGenerator>
    py_IndexGenerator(this_module, "IndexGenerator");

    class_builder<map_to_asu<std::complex<double> > >
    py_map_to_asu(this_module, "map_to_asu");

    class_builder<index_span>
    py_index_span(this_module, "index_span");

    class_builder<join_sets>
    py_join_sets(this_module, "join_sets");

    class_builder<join_bijvoet_mates>
    py_join_bijvoet_mates(this_module, "join_bijvoet_mates");

    py_IndexTableLayoutAdaptor.declare_base(
      py_SymEquivIndex, python::without_downcast);
    py_AsymIndex.declare_base(
      py_SymEquivIndex, python::without_downcast);

  py_SymEquivIndex.def(constructor<>());
  py_SymEquivIndex.def(
    constructor<const Index&, int, int, bool>());
  py_SymEquivIndex.def(&SymEquivIndex::H, "H");
  py_SymEquivIndex.def(&SymEquivIndex::HR, "HR");
  py_SymEquivIndex.def(&SymEquivIndex::HT, "HT");
  py_SymEquivIndex.def(&SymEquivIndex::TBF, "TBF");
  py_SymEquivIndex.def(&SymEquivIndex::HT_angle, "HT_angle");
  py_SymEquivIndex.def(SymEquivIndex_HT_angle_0, "HT_angle");
  py_SymEquivIndex.def(
    &SymEquivIndex::FriedelFlag, "FriedelFlag");
  py_SymEquivIndex.def(SymEquivIndex_Mate_0, "Mate");
  py_SymEquivIndex.def(&SymEquivIndex::Mate, "Mate");
  py_SymEquivIndex.def(
    SymEquivIndex_phase_eq_1, "phase_eq");
  py_SymEquivIndex.def(
    SymEquivIndex_phase_eq_2, "phase_eq");
  py_SymEquivIndex.def(
    SymEquivIndex_phase_in_1, "phase_in");
  py_SymEquivIndex.def(
    SymEquivIndex_phase_in_2, "phase_in");
  py_SymEquivIndex.def(
    SymEquivIndex_complex_eq, "complex_eq");
  py_SymEquivIndex.def(
    SymEquivIndex_complex_in, "complex_in");
  py_SymEquivIndex.def(
    SymEquivIndex_hl_eq, "hl_eq");
  py_SymEquivIndex.def(
    SymEquivIndex_hl_in, "hl_in");

  py_SymEquivIndices.def(constructor<>());
  py_SymEquivIndices.def(constructor<
    sgtbx::SpaceGroup const&,
    Index const&>());
  py_SymEquivIndices.def(
    &SymEquivIndices::getPhaseRestriction, "getPhaseRestriction");
  py_SymEquivIndices.def(
    &SymEquivIndices::isCentric, "isCentric");
  py_SymEquivIndices.def(&SymEquivIndices::N, "N");
  py_SymEquivIndices.def(&SymEquivIndices::M, "M");
  py_SymEquivIndices.def(&SymEquivIndices::fMates, "fMates");
  py_SymEquivIndices.def(&SymEquivIndices::epsilon, "epsilon");
  py_SymEquivIndices.def(&SymEquivIndices::N, "__len__");
  py_SymEquivIndices.def(SymEquivIndices_getitem, "__getitem__");
  py_SymEquivIndices.def(SymEquivIndices_call_1, "__call__");
  py_SymEquivIndices.def(SymEquivIndices_call_2, "__call__");
  py_SymEquivIndices.def(
    &SymEquivIndices::isValidPhase, "isValidPhase");
  py_SymEquivIndices.def(
    SymEquivIndices_isValidPhase_2, "isValidPhase");
  py_SymEquivIndices.def(
    SymEquivIndices_isValidPhase_1, "isValidPhase");

  py_IndexTableLayoutAdaptor.def(constructor<>());
  py_IndexTableLayoutAdaptor.def(
    &IndexTableLayoutAdaptor::H, "H");
  py_IndexTableLayoutAdaptor.def(
    &IndexTableLayoutAdaptor::iColumn, "iColumn");

  py_AsymIndex.def(constructor<>());
  py_AsymIndex.def(constructor<
    const sgtbx::SpaceGroup&,
    const sgtbx::ReciprocalSpaceASU&,
    const Index&>());
  py_AsymIndex.def(constructor<
    const sgtbx::SpaceGroup&,
    const Index&>());
  py_AsymIndex.def(constructor<
    const SymEquivIndices&>());
  py_AsymIndex.def(
    &AsymIndex::one_column, "one_column");
  py_AsymIndex.def(
    &AsymIndex::two_column, "two_column");

    py_IndexGenerator.def(constructor<>());
    py_IndexGenerator.def(constructor<const uctbx::UnitCell&,
                                      const sgtbx::SpaceGroupInfo&,
                                      bool,
                                      double>());
    py_IndexGenerator.def(constructor<const sgtbx::SpaceGroupInfo&,
                                      bool,
                                      const Index&>());
    py_IndexGenerator.def(&IndexGenerator::next, "next");
    py_IndexGenerator.def(IndexGenerator_getitem, "__getitem__");
    py_IndexGenerator.def(&IndexGenerator::ASU, "ASU");

    this_module.def(py_BuildIndices_Resolution_d_min, "BuildIndices");
    this_module.def(py_BuildIndices_MaxIndex, "BuildIndices");

    py_map_to_asu.def(constructor<>());
    py_map_to_asu.def(constructor<
      const sgtbx::SpaceGroupInfo&,
      bool,
      af::shared<Index>,
      af::shared<std::complex<double> >,
      bool>());
    py_map_to_asu.def(constructor<
      const sgtbx::SpaceGroupInfo&,
      bool,
      af::shared<Index>,
      af::shared<std::complex<double> > >());
    py_map_to_asu.def(
      &map_to_asu<std::complex<double> >::friedel_flag,
                                         "friedel_flag");
    py_map_to_asu.def(
      &map_to_asu<std::complex<double> >::asu,
                                         "asu");
    py_map_to_asu.def(
      &map_to_asu<std::complex<double> >::asym_indices,
                                         "asym_indices");
    py_map_to_asu.def(
      &map_to_asu<std::complex<double> >::asym_data_array,
                                         "asym_data_array");

    py_index_span.def(constructor<>());
    py_index_span.def(constructor<af::shared<Index> >());
    py_index_span.def(&index_span::min, "min");
    py_index_span.def(&index_span::max, "max");
    py_index_span.def(&index_span::abs_range, "abs_range");
    py_index_span.def(&index_span::map_grid, "map_grid");
    py_index_span.def(&index_span::is_in_domain, "is_in_domain");

    py_join_sets.def(constructor<>());
    py_join_sets.def(constructor<
      af::shared<Index>,
      af::shared<Index> >());
    py_join_sets.def(&join_sets::pairs, "pairs");
    py_join_sets.def(&join_sets::singles, "singles");
    py_join_sets.def(&join_sets::have_singles, "have_singles");

    py_join_bijvoet_mates.def(constructor<>());
    py_join_bijvoet_mates.def(constructor<
      sgtbx::SpaceGroupInfo const&, af::shared<Index> >());
    py_join_bijvoet_mates.def(constructor<
      cctbx::sgtbx::ReciprocalSpaceASU const&, af::shared<Index> >());
    py_join_bijvoet_mates.def(constructor<
      af::shared<Index> >());
    py_join_bijvoet_mates.def(&join_bijvoet_mates::pairs, "pairs");
    py_join_bijvoet_mates.def(&join_bijvoet_mates::singles, "singles");
    py_join_bijvoet_mates.def(
      &join_bijvoet_mates::have_singles, "have_singles");
    py_join_bijvoet_mates.def(&join_bijvoet_mates::select, "select");

    this_module.def(py_expand_to_p1_4, "expand_to_p1");
    this_module.def(py_expand_to_p1_9, "expand_to_p1");
    this_module.def(py_expand_to_p1_8, "expand_to_p1");
  }

}

BOOST_PYTHON_MODULE_INIT(miller)
{
  boost::python::module_builder this_module("miller");
  init_module(this_module);
}
