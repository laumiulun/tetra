//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PeltierBC.h"

registerMooseObject("TetraApp", PeltierBC);

InputParameters
PeltierBC::validParams()
{
  InputParameters params = ADIntegratedBC::validParams();
  params.addRequiredCoupledVar("elec", "The electrical potential");
  params.addClassDescription("Compute the interface head generated from peltier.");
  return params;
}

PeltierBC::PeltierBC(const InputParameters & parameters)
  : ADIntegratedBC(parameters),
    // _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity")),
    _grad_elec(adCoupledGradient("elec")),
    _seebeck(getADMaterialProperty<Real>("seebeck")),
    _resistance(getADMaterialProperty<Real>("resistance"))
{
}

ADReal
PeltierBC::computeQpResidual()
{
  // return -_test[_i][_qp] * _thermal_conductivity[_qp] * _grad_u[_qp] * _normals[_qp];
  return -_test[_i][_qp] * (_seebeck[_qp] / _resistance[_qp]) * _u[_qp] * _grad_elec[_qp] *
         _normals[_qp];
}
