from __future__ import division, print_function
'''
'''

from iotbx.data_manager import DataManagerBase

# =============================================================================
class NcsSpecDataManager(DataManagerBase):

  datatype = 'ncs_spec'

  # ---------------------------------------------------------------------------
  # Ncs spec
  def add_ncs_spec(self, filename, data):
    return self._add(NcsSpecDataManager.datatype, filename, data)

  def set_default_ncs_spec(self, filename):
    return self._set_default(NcsSpecDataManager.datatype, filename)

  def get_ncs_spec(self, filename=None):
    return self._get(NcsSpecDataManager.datatype, filename)

  def get_ncs_spec_names(self):
    return self._get_names(NcsSpecDataManager.datatype)

  def get_default_ncs_spec_name(self):
    return self._get_default_name(NcsSpecDataManager.datatype)

  def remove_ncs_spec(self, filename):
    return self._remove(NcsSpecDataManager.datatype, filename)

  def has_ncs_specs(self, expected_n=1, exact_count=False, raise_sorry=False):
    return self._has_data(NcsSpecDataManager.datatype, expected_n=expected_n,
                          exact_count=exact_count, raise_sorry=raise_sorry)

  def process_ncs_spec_file(self, filename):
    return self._process_file(NcsSpecDataManager.datatype, filename)

  def write_ncs_spec_file(self, filename, ncs_str, overwrite=False):
    self._write_text(NcsSpecDataManager.datatype, filename,
                     ncs_str, overwrite=overwrite)

# =============================================================================
# end
