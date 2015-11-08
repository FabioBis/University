(* ::Package:: *)

(* ::Input:: *)
(*BeginPackage["Project`"];*)
(**)
(*MyCircularity::usage "MyCircularity[image, method] gives the circularity mesurements of the main shape in the figure 'image' using the method 'method'";*)
(**)
(*(*Begin["Private`"]*)*)
(*MyCircularity[image_, method_] := *)
(*Module[{img = image, algo = method, shape, area, perimeter, circularity},*)
(*shape = MorphologicalBinarize[image];*)
(*shape = DeleteSmallComponents[shape];*)
(*area = ComponentMeasurements[shape, "Area"];*)
(*area = area /. Rule -> (#2&);*)
(*area = area[[1]];*)
(*perimeter = ComponentMeasurements[shape, "PerimeterLength"];*)
(*perimeter = perimeter/. Rule -> (#2&);*)
(*perimeter = perimeter[[1]];*)
(*(* Plain Circularity *)*)
(*circularity = 4*Pi*area/perimeter^2;*)
(*Print["Area: ", area];*)
(*Print["Perimeter: ", perimeter];Print["Circularity: ",circularity];*)
(*]*)
(**)
(*MyModule[M_] :=*)
(*Module[{m = M},*)
(*Print["m = ", m];*)
(*Y = m + 1;*)
(*Y*)
(*]*)
(*(*End[]*)*)
(**)
(**)
(*EndPackage[]*)