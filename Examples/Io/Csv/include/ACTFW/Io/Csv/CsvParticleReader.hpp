// This file is part of the Acts project.
//
// Copyright (C) 2017-2019 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <Acts/Utilities/Logger.hpp>
#include <memory>
#include <string>

#include "ACTFW/Framework/IReader.hpp"

namespace FW {

/// Read particles in the TrackML comma-separated-value format.
///
/// This reads one file per event in the configured input directory
/// and filename. Files are assumed to be named using the following schema
///
///     event000000001-<stem>.csv
///     event000000002-<stem>.csv
///
/// and each line in the file corresponds to one particle. The
/// input filename can be configured and defaults to `particles.csv`.
class CsvParticleReader final : public IReader {
 public:
  struct Config {
    /// Where to read input files from.
    std::string inputDir;
    /// Input filename stem.
    std::string inputStem = "particles";
    /// Which particle collection to read into.
    std::string outputParticles;
  };

  /// Construct the particle reader.
  ///
  /// @params cfg is the configuration object
  /// @params lvl is the logging level
  CsvParticleReader(const Config& cfg, Acts::Logging::Level lvl);

  std::string name() const final override;

  /// Return the available events range.
  std::pair<size_t, size_t> availableEvents() const final override;

  /// Read out data from the input stream.
  ProcessCode read(const FW::AlgorithmContext& ctx) final override;

 private:
  Config m_cfg;
  std::pair<size_t, size_t> m_eventsRange;
  std::unique_ptr<const Acts::Logger> m_logger;

  const Acts::Logger& logger() const { return *m_logger; }
};

}  // namespace FW
