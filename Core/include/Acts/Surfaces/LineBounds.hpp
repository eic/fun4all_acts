// This file is part of the Acts project.
//
// Copyright (C) 2016-2020 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Acts/Surfaces/SurfaceBounds.hpp"
#include "Acts/Utilities/Definitions.hpp"

#include <array>
#include <vector>

namespace Acts {

/// @class LineBounds
///
/// Bounds for a LineSurface.
///

class LineBounds : public SurfaceBounds {
 public:
  enum BoundValues : int { eR = 0, eHalfLengthZ = 1, eSize = 2 };

  LineBounds() = delete;

  /// Constructor
  ///
  /// @param r is the radius of the cylinder, default = 0.
  /// @param halfZ is the half length in z, defualt = 0.
  LineBounds(double r, double halfZ)
      : m_values({std::abs(r), std::abs(halfZ)}) {}

  /// Constructor - from fixed size array
  ///
  /// @param values The parameter values
  LineBounds(const std::array<double, eSize>& values) : m_values(values) {}

  ~LineBounds() override = default;

  LineBounds* clone() const final;

  BoundsType type() const final;

  /// Return the bound values as dynamically sized vector
  ///
  /// @return this returns a copy of the internal values
  std::vector<double> values() const final;

  /// Inside check for the bounds object driven by the boundary check directive
  /// Each Bounds has a method inside, which checks if a LocalPosition is inside
  /// the bounds  Inside can be called without/with tolerances.
  ///
  /// @param lposition Local position (assumed to be in right surface frame)
  /// @param bcheck boundary check directive
  ///
  /// @return boolean indicator for the success of this operation
  bool inside(const Vector2D& lposition,
              const BoundaryCheck& bcheck) const final;

  /// Minimal distance to boundary ( > 0 if outside and <=0 if inside)
  ///
  /// @param lposition is the local position to check for the distance
  ///
  /// @return is a signed distance parameter
  double distanceToBoundary(const Vector2D& lposition) const final;

  /// Output Method for std::ostream
  ///
  /// @param sl is the ostream to be dumped into
  std::ostream& toStream(std::ostream& sl) const final;

  /// Access to the bound values
  /// @param bValue the class nested enum for the array access
  double get(BoundValues bValue) const { return m_values[bValue]; }

 private:
  std::array<double, eSize> m_values;
};

inline std::vector<double> LineBounds::values() const {
  std::vector<double> valvector;
  valvector.insert(valvector.begin(), m_values.begin(), m_values.end());
  return valvector;
}

}  // namespace Acts