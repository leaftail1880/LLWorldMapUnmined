/**
 *
 * General block textures
 * ======================
 *
 *
 * This script assigns textures to vanilla blocks.
 *
 *
 */

woodenMaterials = [
    "acacia",
    "birch",
    "darkoak",
    "jungle",
    "oak",
    "spruce",
    "crimson",
    "warped",
    "mangrove",
    "bamboo",
    "cherry",
];

colors = [
    "white",
    "orange",
    "magenta",
    "light_blue",
    "yellow",
    "lime",
    "pink",
    "gray",
    "silver",
    "cyan",
    "purple",
    "blue",
    "brown",
    "green",
    "red",
    "black",
];
class StyleSheet {

    build(builder) {
        if (!builder.usingTextures)
            return;

        this.addDefault(builder);

        this.addWoodenProducts(builder);
        this.addStoneProducts(builder);
        this.addBrickProducts(builder);
        this.addSandstoneProducts(builder);
        this.addCopperProducts(builder);
        this.addOtherProducts(builder);

        this.addCarpets(builder);

        this.addPressurePlates(builder);

        this.addRails(builder);
    }


    addDefault(builder) {
        builder.style("*:*").texture("*_stage3; *_top; *");

        builder.style("*_log[axis:y]").texture("*_top");

        builder.style("#grass, #grassblock").grassTint();
        builder.style("#leaves,#vine").foliageTint();
        builder.style("azalea_leaves, cherry_leaves").withoutTint();

        builder.style("grass_block, dirt, dirt_path, gravel, sand, red_sand, snow, snow_block, snow_layer").randomRotation().randomZFlip().randomXFlip();
        builder.style("stone").randomZFlip().randomXFlip();

        builder.style("lava").texture("lava_still");
        builder.style("flowing_lava").texture("lava_flow");

        builder.style("water").texture("water_still");
        builder.style("flowing_water").texture("water_flow");

        builder.style("#water").waterTint();

        builder.style("fire").texture("fire_0");
        builder.style("soul_fire").texture("soul_fire_0");
        builder.style("campfire").texture("campfire_fire");
        builder.style("soul_campfire").texture("soul_campfire_fire");

        builder.style("snow_block, snow_layer").texture("snow");

        builder.style("smooth_sandstone").texture("sandstone_top");

        builder.style("hay_block").texture("*_side");
        builder.style("wall_torch").texture("torch");

        builder.style("grindstone").texture("grindstone_side");
        builder.style("water_cauldron").texture("cauldron_top");

        builder.style("dispenser").texture("dispenser_front");
        builder.style("dropper").texture("dropper_front");

        builder.style("beehive").texture("beehive_front_honey");
        builder.style("beehive[honey_level:0]").texture("beehive_front");

        builder.style("bamboo").texture("bamboo_stage0");

        builder.style("sticky_piston").texture("piston_top_sticky");
        builder.style("piston_head").texture("piston_top");
        builder.style("piston_head[type:sticky]").texture("piston_top_sticky");

        builder.style("*_glazed_terracotta[facing:north]").rotate(180);
        builder.style("*_glazed_terracotta[facing:east]").rotate(270);
        builder.style("*_glazed_terracotta[facing:south]").rotate(0);
        builder.style("*_glazed_terracotta[facing:west]").rotate(90);

    }

    addRails(builder) {

        builder.style("(rail, powered_rail, activator_rail) ([shape:east_west], [shape:ascending_west], [shape:ascending_east])").texture("*").rotate(90);

        builder.style("rail[shape:south_east]").texture("rail_corner").rotate(0);
        builder.style("rail[shape:south_west]").texture("rail_corner").rotate(90);
        builder.style("rail[shape:north_west]").texture("rail_corner").rotate(180);
        builder.style("rail[shape:north_east]").texture("rail_corner").rotate(270);
    }

    addWoodenProducts(builder) {
        woodenMaterials.forEach(m => {
            builder.style(m + "_stairs").texture(m + "_planks");
            builder.style(m + "_slab").texture(m + "_planks");
            builder.style(m + "_fence").texture(m + "_planks");
            builder.style(m + "_fence_gate").texture(m + "_planks");
            builder.style(m + "_pressure_plate").texture(m + "_planks");

            builder.style("stripped_" + m + "_wood").texture("stripped_" + m + "_log");

            builder.style("stripped_" + m + "_stem").texture("stripped_" + m + "_stem_top");
            builder.style("stripped_" + m + "_hyphae").texture("stripped_" + m + "_stem");

            builder.style("stripped_" + m + "_log[axis:y]").texture("stripped_" + m + "_log_top");
            builder.style("stripped_" + m + "_log[axis:x]").texture("stripped_" + m + "_log");
            builder.style("stripped_" + m + "_log[axis:z]").texture("stripped_" + m + "_log").rotate(90);
        });
    }

    addCarpets(builder) {
        colors.forEach(c => {
            builder.style(c + "_carpet").texture(c + "_wool");
        });
    }

    addPressurePlates(builder) {
        builder.style("heavy_weighted_pressure_plate").texture("iron_block");
        builder.style("light_weighted_pressure_plate").texture("gold_block");
    }


    addStoneProducts(builder) {
        let materials = [
            "andesite",
            "blackstone",
            "cobblestone",
            "cobbled_deepslate",
            "dark_prismarine",
            "diorite",
            "granite",
            "mossy_cobblestone",
            "prismarine",
            "smooth_stone",
            "stone",

            "polished_andesite",
            "polished_blackstone",
            "polished_deepslate",
            "polished_diorite",
            "polished_granite",
        ];


        materials.forEach(m => {
            builder.style(m + "_stairs").texture(m);
            builder.style(m + "_slab").texture(m);
            builder.style(m + "_wall").texture(m);
            builder.style(m + "_pressure_plate").texture(m);
        });
    }

    addCopperProducts(builder) {
        let materials = [
            "cut_copper",
            "exposed_cut_copper",
            "oxidized_cut_copper",
            "weathered_cut_copper",
        ];
        let waxed = [
            "",
            "waxed_",
        ];

        waxed.forEach(w => {
            materials.forEach(m => {
                builder.style(w + m).texture(m);
                builder.style(w + m + "_stairs").texture(m);
                builder.style(w + m + "_slab").texture(m);
                builder.style(w + m + "_wall").texture(m);
                builder.style(w + m + "_pressure_plate").texture(m);
            });
        });

        let blocks = [
            "copper_block",
            "exposed_copper",
            "oxidized_copper",
            "weathered_copper",
        ];

        waxed.forEach(w => {
            blocks.forEach(m => {
                builder.style(w + m).texture(m);
            });
        });
    }
    addBrickProducts(builder) {
        let materials = [
            "brick",
            "deepslate_brick",
            "deepslate_tile",
            "end_stone_brick",
            "mossy_stone_brick",
            "mud_brick",
            "nether_brick",
            "polished_blackstone_brick",
            "prismarine_brick",
            "stone_brick",
            "red_nether_brick",
        ];


        materials.forEach(m => {
            builder.style(m + "_stairs").texture(m + "s");
            builder.style(m + "_slab").texture(m + "s");
            builder.style(m + "_wall").texture(m + "s");
        });
    }

    addSandstoneProducts(builder) {
        let materials = [
            "sandstone",
            "red_sandstone",
        ];


        materials.forEach(m => {
            builder.style(m + "_stairs").texture(m + "_top");
            builder.style(m + "_slab").texture(m + "_top");
            builder.style(m + "_wall").texture(m + "_top");
            builder.style("smooth_" + m + "_stairs").texture(m + "_top");
            builder.style("smooth_" + m + "_slab").texture(m + "_top");
            builder.style("smooth_" + m + "_wall").texture(m + "_top");
            builder.style("cut_" + m + "_stairs").texture(m + "_top");
            builder.style("cut_" + m + "_slab").texture(m + "_top");
            builder.style("cut_" + m + "_wall").texture(m + "_top");
        });

        builder.style("smooth_sandstone").texture("sandstone_top");
        builder.style("smooth_red_sandstone").texture("red_sandstone_top");
    }

    addOtherProducts(builder) {
        let materials = {
            "quartz": "quartz_block_top",
            "smooth_quartz": "quartz_block_bottom",
            "purpur": "purpur_block",
        };


        for (const m in materials) {
            let x = materials[m];
            builder.style(m + "_stairs").texture(x);
            builder.style(m + "_slab").texture(x);
            builder.style(m + "_wall").texture(x);
        }
    }


}