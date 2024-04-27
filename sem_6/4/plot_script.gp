set terminal pngcairo enhanced color size 1000,1000
set output 'Triangulation.png'
f(x, y) =  ((x*y*x) + x*x) 
p_0(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && (0.6 + 1*(x - -1)) < y && y < 1) ? 1.96667*(x**2) + -1.78333*(x*y) + 2.84217e-14*(y**2) + 1.72389*(x) + -0.789444*(y) + 0.76313: 1/0
p_1(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && 0.6 < y && y < (0.6 + 1*(x - -1))) ? 1.63333*(x**2) + -1.41667*(x*y) + -2.84217e-14*(y**2) + 0.897222*(x) + -0.496111*(y) + 0.314204: 1/0
p_2(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && (0.6 + 1*(x - -0.6)) < y && y < 1) ? 1.96667*(x**2) + -0.983333*(x*y) + 4.72511e-13*(y**2) + 0.950556*(x) + -0.236111*(y) + 0.228241: 1/0
p_3(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && 0.6 < y && y < (0.6 + 1*(x - -0.6))) ? 1.63333*(x**2) + -0.616667*(x*y) + 3.01981e-14*(y**2) + 0.390556*(x) + -0.0894444*(y) + 0.0566481: 1/0
p_4(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && (0.6 + 1*(x - -0.2)) < y && y < 1) ? 1.96667*(x**2) + -0.183333*(x*y) + 1.47748e-12*(y**2) + 0.177222*(x) + -0.00277778*(y) + 0.00268519: 1/0
p_5(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && 0.6 < y && y < (0.6 + 1*(x - -0.2))) ? 1.63333*(x**2) + 0.183333*(x*y) + 4.60076e-13*(y**2) + -0.116111*(x) + -0.00277778*(y) + 0.00175926: 1/0
p_6(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && (0.6 + 1*(x - 0.2)) < y && y < 1) ? 1.96667*(x**2) + 0.616667*(x*y) + -1.77636e-15*(y**2) + -0.596111*(x) + -0.0894444*(y) + 0.086463: 1/0
p_7(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && 0.6 < y && y < (0.6 + 1*(x - 0.2))) ? 1.63333*(x**2) + 0.983333*(x*y) + 1.13687e-13*(y**2) + -0.622778*(x) + -0.236111*(y) + 0.149537: 1/0
p_8(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && (0.6 + 1*(x - 0.6)) < y && y < 1) ? 1.96667*(x**2) + 1.41667*(x*y) + -1.27898e-13*(y**2) + -1.36944*(x) + -0.496111*(y) + 0.479574: 1/0
p_9(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && 0.6 < y && y < (0.6 + 1*(x - 0.6))) ? 1.63333*(x**2) + 1.78333*(x*y) + 2.41585e-13*(y**2) + -1.12944*(x) + -0.789444*(y) + 0.499981: 1/0
p_10(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && (0.2 + 1*(x - -1)) < y && y < 0.6) ? 1.56667*(x**2) + -1.78333*(x*y) + -6.39488e-14*(y**2) + 1.01056*(x) + -0.789444*(y) + 0.447352: 1/0
p_11(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && 0.2 < y && y < (0.2 + 1*(x - -1))) ? 1.23333*(x**2) + -1.41667*(x*y) + -2.4869e-14*(y**2) + 0.330556*(x) + -0.496111*(y) + 0.115759: 1/0
p_12(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && (0.2 + 1*(x - -0.6)) < y && y < 0.6) ? 1.56667*(x**2) + -0.983333*(x*y) + 1.77636e-14*(y**2) + 0.557222*(x) + -0.236111*(y) + 0.133796: 1/0
p_13(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && 0.2 < y && y < (0.2 + 1*(x - -0.6))) ? 1.23333*(x**2) + -0.616667*(x*y) + 8.88178e-16*(y**2) + 0.143889*(x) + -0.0894444*(y) + 0.0208704: 1/0
p_14(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && (0.2 + 1*(x - -0.2)) < y && y < 0.6) ? 1.56667*(x**2) + -0.183333*(x*y) + 3.10862e-14*(y**2) + 0.103889*(x) + -0.00277778*(y) + 0.00157407: 1/0
p_15(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && 0.2 < y && y < (0.2 + 1*(x - -0.2))) ? 1.23333*(x**2) + 0.183333*(x*y) + 1.17684e-14*(y**2) + -0.0427778*(x) + -0.00277778*(y) + 0.000648148: 1/0
p_16(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && (0.2 + 1*(x - 0.2)) < y && y < 0.6) ? 1.56667*(x**2) + 0.616667*(x*y) + 4.44089e-15*(y**2) + -0.349444*(x) + -0.0894444*(y) + 0.0506852: 1/0
p_17(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && 0.2 < y && y < (0.2 + 1*(x - 0.2))) ? 1.23333*(x**2) + 0.983333*(x*y) + 0*(y**2) + -0.229444*(x) + -0.236111*(y) + 0.0550926: 1/0
p_18(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && (0.2 + 1*(x - 0.6)) < y && y < 0.6) ? 1.56667*(x**2) + 1.41667*(x*y) + 1.42109e-14*(y**2) + -0.802778*(x) + -0.496111*(y) + 0.28113: 1/0
p_19(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && 0.2 < y && y < (0.2 + 1*(x - 0.6))) ? 1.23333*(x**2) + 1.78333*(x*y) + -5.68434e-14*(y**2) + -0.416111*(x) + -0.789444*(y) + 0.184204: 1/0
p_20(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && (-0.2 + 1*(x - -1)) < y && y < 0.2) ? 1.16667*(x**2) + -1.78333*(x*y) + 3.55271e-14*(y**2) + 0.297222*(x) + -0.789444*(y) + 0.131574: 1/0
p_21(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && -0.2 < y && y < (-0.2 + 1*(x - -1))) ? 0.833333*(x**2) + -1.41667*(x*y) + 7.10543e-15*(y**2) + -0.236111*(x) + -0.496111*(y) + -0.0826852: 1/0
p_22(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && (-0.2 + 1*(x - -0.6)) < y && y < 0.2) ? 1.16667*(x**2) + -0.983333*(x*y) + -5.32907e-15*(y**2) + 0.163889*(x) + -0.236111*(y) + 0.0393519: 1/0
p_23(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && -0.2 < y && y < (-0.2 + 1*(x - -0.6))) ? 0.833333*(x**2) + -0.616667*(x*y) + 8.88178e-16*(y**2) + -0.102778*(x) + -0.0894444*(y) + -0.0149074: 1/0
p_24(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && (-0.2 + 1*(x - -0.2)) < y && y < 0.2) ? 1.16667*(x**2) + -0.183333*(x*y) + 2.22045e-16*(y**2) + 0.0305556*(x) + -0.00277778*(y) + 0.000462963: 1/0
p_25(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && -0.2 < y && y < (-0.2 + 1*(x - -0.2))) ? 0.833333*(x**2) + 0.183333*(x*y) + 0*(y**2) + 0.0305556*(x) + -0.00277778*(y) + -0.000462963: 1/0
p_26(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && (-0.2 + 1*(x - 0.2)) < y && y < 0.2) ? 1.16667*(x**2) + 0.616667*(x*y) + -8.88178e-16*(y**2) + -0.102778*(x) + -0.0894444*(y) + 0.0149074: 1/0
p_27(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && -0.2 < y && y < (-0.2 + 1*(x - 0.2))) ? 0.833333*(x**2) + 0.983333*(x*y) + 1.59872e-14*(y**2) + 0.163889*(x) + -0.236111*(y) + -0.0393519: 1/0
p_28(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && (-0.2 + 1*(x - 0.6)) < y && y < 0.2) ? 1.16667*(x**2) + 1.41667*(x*y) + 7.4607e-14*(y**2) + -0.236111*(x) + -0.496111*(y) + 0.0826852: 1/0
p_29(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && -0.2 < y && y < (-0.2 + 1*(x - 0.6))) ? 0.833333*(x**2) + 1.78333*(x*y) + -4.26326e-14*(y**2) + 0.297222*(x) + -0.789444*(y) + -0.131574: 1/0
p_30(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && (-0.6 + 1*(x - -1)) < y && y < -0.2) ? 0.766667*(x**2) + -1.78333*(x*y) + 0*(y**2) + -0.416111*(x) + -0.789444*(y) + -0.184204: 1/0
p_31(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && -0.6 < y && y < (-0.6 + 1*(x - -1))) ? 0.433333*(x**2) + -1.41667*(x*y) + 3.55271e-15*(y**2) + -0.802778*(x) + -0.496111*(y) + -0.28113: 1/0
p_32(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && (-0.6 + 1*(x - -0.6)) < y && y < -0.2) ? 0.766667*(x**2) + -0.983333*(x*y) + 0*(y**2) + -0.229444*(x) + -0.236111*(y) + -0.0550926: 1/0
p_33(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && -0.6 < y && y < (-0.6 + 1*(x - -0.6))) ? 0.433333*(x**2) + -0.616667*(x*y) + -8.88178e-16*(y**2) + -0.349444*(x) + -0.0894444*(y) + -0.0506852: 1/0
p_34(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && (-0.6 + 1*(x - -0.2)) < y && y < -0.2) ? 0.766667*(x**2) + -0.183333*(x*y) + -1.08802e-14*(y**2) + -0.0427778*(x) + -0.00277778*(y) + -0.000648148: 1/0
p_35(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && -0.6 < y && y < (-0.6 + 1*(x - -0.2))) ? 0.433333*(x**2) + 0.183333*(x*y) + 1.87628e-14*(y**2) + 0.103889*(x) + -0.00277778*(y) + -0.00157407: 1/0
p_36(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && (-0.6 + 1*(x - 0.2)) < y && y < -0.2) ? 0.766667*(x**2) + 0.616667*(x*y) + 5.55112e-15*(y**2) + 0.143889*(x) + -0.0894444*(y) + -0.0208704: 1/0
p_37(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && -0.6 < y && y < (-0.6 + 1*(x - 0.2))) ? 0.433333*(x**2) + 0.983333*(x*y) + 3.90799e-14*(y**2) + 0.557222*(x) + -0.236111*(y) + -0.133796: 1/0
p_38(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && (-0.6 + 1*(x - 0.6)) < y && y < -0.2) ? 0.766667*(x**2) + 1.41667*(x*y) + -8.88178e-14*(y**2) + 0.330556*(x) + -0.496111*(y) + -0.115759: 1/0
p_39(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && -0.6 < y && y < (-0.6 + 1*(x - 0.6))) ? 0.433333*(x**2) + 1.78333*(x*y) + 1.20792e-13*(y**2) + 1.01056*(x) + -0.789444*(y) + -0.447352: 1/0
p_40(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && (-1 + 1*(x - -1)) < y && y < -0.6) ? 0.366667*(x**2) + -1.78333*(x*y) + 0*(y**2) + -1.12944*(x) + -0.789444*(y) + -0.499981: 1/0
p_41(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-1 < x && x < -0.6 && -1 < y && y < (-1 + 1*(x - -1))) ? 0.0333333*(x**2) + -1.41667*(x*y) + 1.33227e-15*(y**2) + -1.36944*(x) + -0.496111*(y) + -0.479574: 1/0
p_42(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && (-1 + 1*(x - -0.6)) < y && y < -0.6) ? 0.366667*(x**2) + -0.983333*(x*y) + -6.21725e-15*(y**2) + -0.622778*(x) + -0.236111*(y) + -0.149537: 1/0
p_43(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.6 < x && x < -0.2 && -1 < y && y < (-1 + 1*(x - -0.6))) ? 0.0333333*(x**2) + -0.616667*(x*y) + 2.498e-15*(y**2) + -0.596111*(x) + -0.0894444*(y) + -0.086463: 1/0
p_44(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && (-1 + 1*(x - -0.2)) < y && y < -0.6) ? 0.366667*(x**2) + -0.183333*(x*y) + 4.94049e-15*(y**2) + -0.116111*(x) + -0.00277778*(y) + -0.00175926: 1/0
p_45(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (-0.2 < x && x < 0.2 && -1 < y && y < (-1 + 1*(x - -0.2))) ? 0.0333333*(x**2) + 0.183333*(x*y) + -1.75998e-13*(y**2) + 0.177222*(x) + -0.00277778*(y) + -0.00268519: 1/0
p_46(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && (-1 + 1*(x - 0.2)) < y && y < -0.6) ? 0.366667*(x**2) + 0.616667*(x*y) + 7.77156e-16*(y**2) + 0.390556*(x) + -0.0894444*(y) + -0.0566481: 1/0
p_47(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.2 < x && x < 0.6 && -1 < y && y < (-1 + 1*(x - 0.2))) ? 0.0333333*(x**2) + 0.983333*(x*y) + -1.42553e-13*(y**2) + 0.950556*(x) + -0.236111*(y) + -0.228241: 1/0
p_48(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && (-1 + 1*(x - 0.6)) < y && y < -0.6) ? 0.366667*(x**2) + 1.41667*(x*y) + -9.50351e-14*(y**2) + 0.897222*(x) + -0.496111*(y) + -0.314204: 1/0
p_49(x, y) =  ( (x/1) + (y/1) > 1 || (x/1) + (y/1) < -1 || -(x/1) + (y/1) > 1 || -(x/1) + (y/1) < -1) ? 1/0 : (0.6 < x && x < 1 && -1 < y && y < (-1 + 1*(x - 0.6))) ? 0.0333333*(x**2) + 1.78333*(x*y) + -8.9706e-14*(y**2) + 1.72389*(x) + -0.789444*(y) + -0.76313: 1/0
set xlabel 'x'
set ylabel 'y'
set zlabel 'z'
unset colorbox
set xrange[-1: 1]
set yrange[-1: 1]
splot f(x, y) lc rgb 'green' , p_0(x, y) lc rgb 'red' notitle, p_1(x, y) lc rgb 'blue' notitle, p_2(x, y) lc rgb 'red' notitle, p_3(x, y) lc rgb 'blue' notitle, p_4(x, y) lc rgb 'red' notitle, p_5(x, y) lc rgb 'blue' notitle, p_6(x, y) lc rgb 'red' notitle, p_7(x, y) lc rgb 'blue' notitle, p_8(x, y) lc rgb 'red' notitle, p_9(x, y) lc rgb 'blue' notitle, p_10(x, y) lc rgb 'red' notitle, p_11(x, y) lc rgb 'blue' notitle, p_12(x, y) lc rgb 'red' notitle, p_13(x, y) lc rgb 'blue' notitle, p_14(x, y) lc rgb 'red' notitle, p_15(x, y) lc rgb 'blue' notitle, p_16(x, y) lc rgb 'red' notitle, p_17(x, y) lc rgb 'blue' notitle, p_18(x, y) lc rgb 'red' notitle, p_19(x, y) lc rgb 'blue' notitle, p_20(x, y) lc rgb 'red' notitle, p_21(x, y) lc rgb 'blue' notitle, p_22(x, y) lc rgb 'red' notitle, p_23(x, y) lc rgb 'blue' notitle, p_24(x, y) lc rgb 'red' notitle, p_25(x, y) lc rgb 'blue' notitle, p_26(x, y) lc rgb 'red' notitle, p_27(x, y) lc rgb 'blue' notitle, p_28(x, y) lc rgb 'red' notitle, p_29(x, y) lc rgb 'blue' notitle, p_30(x, y) lc rgb 'red' notitle, p_31(x, y) lc rgb 'blue' notitle, p_32(x, y) lc rgb 'red' notitle, p_33(x, y) lc rgb 'blue' notitle, p_34(x, y) lc rgb 'red' notitle, p_35(x, y) lc rgb 'blue' notitle, p_36(x, y) lc rgb 'red' notitle, p_37(x, y) lc rgb 'blue' notitle, p_38(x, y) lc rgb 'red' notitle, p_39(x, y) lc rgb 'blue' notitle, p_40(x, y) lc rgb 'red' notitle, p_41(x, y) lc rgb 'blue' notitle, p_42(x, y) lc rgb 'red' notitle, p_43(x, y) lc rgb 'blue' notitle, p_44(x, y) lc rgb 'red' notitle, p_45(x, y) lc rgb 'blue' notitle, p_46(x, y) lc rgb 'red' notitle, p_47(x, y) lc rgb 'blue' notitle, p_48(x, y) lc rgb 'red' notitle, p_49(x, y) lc rgb 'blue' notitle