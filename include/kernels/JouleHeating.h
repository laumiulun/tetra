// Including the "ADKernel" base class here so we can extend it
#include "ADKernelValue.h"

/**
 * Computes the residual contribution: grad_u - S(T) * grad_temp
 */
class JouleHeating : public ADKernelValue
{
public:
  static InputParameters validParams();

  JouleHeating(const InputParameters & parameters);

protected:
  /// ADKernel objects must override precomputeQpResidual
  virtual ADReal precomputeQpResidual() override;

  /// The variables which hold the value for seabeck
  // const ADVariableValue & _temp;

  // const ADMaterialProperty<Real> & _seebeck;
  const ADMaterialProperty<Real> & _resistance;
};
